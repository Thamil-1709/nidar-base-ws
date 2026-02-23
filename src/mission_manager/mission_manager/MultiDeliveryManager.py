#!/usr/bin/env python3
"""
multi_delivery_offboard_manager.py
====================================
Delivery drone that visits MULTIPLE GPS waypoints in sequence.
At each waypoint it calls the /servo/release service to drop a payload
via a servo indexed 0–6.

Action Interface  : MultiDeliveryActionTrigger
  Goal  : DeliveryWaypoint[] waypoints   (lat, lon, alt, servo_index)
  Result: float64 success
  Feedback: uint32 waypoint_index, uint32 total_waypoints,
            float64 current_lat, float64 current_lon, float64 current_alt,
            float64 distance_to_next

Service Interface : ServoRelease (mission_interfaces/srv)
  Request : uint8  servo_index   (0–6)
  Response: bool   success
            string message

Assumed .action file (MultiDeliveryActionTrigger.action):
------------------------------------------------------------
  DeliveryWaypoint[] waypoints
  ---
  float64 success
  ---
  uint32  waypoint_index
  uint32  total_waypoints
  float64 current_lat
  float64 current_lon
  float64 current_alt
  float64 distance_to_next

Assumed .msg file (DeliveryWaypoint.msg):
------------------------------------------
  float64 latitude
  float64 longitude
  float64 altitude
  uint8   servo_index

Assumed .srv file (ServoRelease.srv):
--------------------------------------
  uint8  servo_index
  ---
  bool   success
  string message
"""

import rclpy
import asyncio
import threading
import time
import math

from rclpy.node import Node
from rclpy.action import ActionServer, GoalResponse, CancelResponse
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import ReentrantCallbackGroup

from std_msgs.msg import String, Float32
from geometry_msgs.msg import Vector3

from mavsdk import System
from mavsdk.offboard import OffboardError, PositionNedYaw

from mission_interfaces.action import MultiDeliveryActionTrigger
from mission_interfaces.srv import ServoRelease


# ================= CONFIG =================
CRUISE_ALT_M          = 10.0   # Default cruise altitude if waypoint alt == 0 (m)
SETPOINT_RATE_HZ      = 10     # Offboard setpoint frequency (Hz)
ARRIVAL_RADIUS_M      = 2.0    # Horizontal distance to consider waypoint reached (m)
HOLD_TIME_SEC         = 3      # Hover time before servo trigger at each waypoint (s)
POST_DROP_HOLD_SEC    = 2      # Hover time after servo trigger before moving on (s)
BATTERY_RTL_THRESHOLD = 0.25   # Battery fraction below which RTL is forced
MAX_MISSION_TIME_SEC  = 1200   # Hard mission timeout (s) — 20 min
TAKEOFF_WAIT_SEC      = 5      # Seconds to wait after takeoff command
SERVO_TIMEOUT_SEC     = 5.0    # Max time to wait for servo service response (s)
VALID_SERVO_INDICES   = range(0, 7)   # 0–6 inclusive
MAVSDK_ADDRESS        = "udp://:14540"


# ================= UTILS =================

def haversine(lat1: float, lon1: float, lat2: float, lon2: float) -> float:
    """Great-circle distance in metres between two GPS coordinates."""
    R = 6_371_000.0
    p1, p2 = math.radians(lat1), math.radians(lat2)
    dp = math.radians(lat2 - lat1)
    dl = math.radians(lon2 - lon1)
    a = math.sin(dp / 2) ** 2 + math.cos(p1) * math.cos(p2) * math.sin(dl / 2) ** 2
    return 2 * R * math.atan2(math.sqrt(a), math.sqrt(1 - a))


def bearing_deg(lat1: float, lon1: float, lat2: float, lon2: float) -> float:
    """Initial bearing (0–360°) from point 1 toward point 2."""
    y = math.sin(math.radians(lon2 - lon1)) * math.cos(math.radians(lat2))
    x = (
        math.cos(math.radians(lat1)) * math.sin(math.radians(lat2))
        - math.sin(math.radians(lat1))
        * math.cos(math.radians(lat2))
        * math.cos(math.radians(lon2 - lon1))
    )
    return (math.degrees(math.atan2(y, x)) + 360) % 360


def gps_to_ned(
    home_lat: float, home_lon: float, lat: float, lon: float
) -> tuple[float, float]:
    """Convert GPS coordinate to NED (North, East) metres offset from home."""
    north = haversine(home_lat, home_lon, lat, home_lon)
    east  = haversine(home_lat, home_lon, home_lat, lon)
    if lat < home_lat:
        north *= -1
    if lon < home_lon:
        east *= -1
    return north, east


# ================= NODE =================

class MultiDeliveryOffboardManager(Node):
    """
    ROS 2 action server that flies the delivery drone to multiple GPS
    waypoints in sequence, hovering at each one and calling the
    /servo/release service to drop the payload before moving on.

    Multi-waypoint flow per goal
    ────────────────────────────
    arm → takeoff → for each waypoint:
        fly (offboard NED control loop)
        → hold HOLD_TIME_SEC
        → call /servo/release (servo_index from waypoint)
        → hold POST_DROP_HOLD_SEC
    → stop offboard → RTL → wait for landing
    """

    def __init__(self):
        super().__init__("multi_delivery_offboard_manager")
        self.get_logger().info("Multi-Delivery Offboard Manager starting…")

        # ---------- internal state ----------
        self._active_goal_handle  = None
        self._cancel_requested    = False
        self._mav_ready           = False
        self.battery              = 1.0     # fraction 0–1, continuously updated
        self.missions_completed   = 0
        self.payloads_delivered   = 0

        # ---------- publishers ----------
        self.state_pub     = self.create_publisher(String,  "/delivery/state",           10)
        self.battery_pub   = self.create_publisher(Float32, "/delivery/battery",          10)
        self.alt_pub       = self.create_publisher(Float32, "/delivery/altitude",          10)
        self.att_pub       = self.create_publisher(Vector3, "/delivery/attitude",          10)
        self.mission_pub   = self.create_publisher(String,  "/delivery/missions_completed",10)
        self.payload_pub   = self.create_publisher(String,  "/delivery/payloads_delivered",10)
        self.wp_pub        = self.create_publisher(String,  "/delivery/current_waypoint",  10)

        self._publish_state("Standby")

        # ---------- callback group (reentrant so service + action can overlap) ----------
        self._cb_group = ReentrantCallbackGroup()

        # ---------- servo release service client ----------
        self.servo_client = self.create_client(
            ServoRelease,
            "/servo/release",
            callback_group=self._cb_group,
        )

        # ---------- async event loop in dedicated thread ----------
        self.loop = asyncio.new_event_loop()
        threading.Thread(target=self._run_loop, daemon=True).start()

        # ---------- MAVSDK ----------
        self.drone = System()
        asyncio.run_coroutine_threadsafe(self._connect(), self.loop)

        # ---------- action server ----------
        self.action_server = ActionServer(
            self,
            MultiDeliveryActionTrigger,
            "start_multi_delivery",
            execute_callback=self.execute_callback,
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback,
            callback_group=self._cb_group,
        )

        self.get_logger().info("Multi-Delivery Offboard Manager ready")

    # ================================================================
    # EVENT LOOP
    # ================================================================

    def _run_loop(self):
        asyncio.set_event_loop(self.loop)
        self.loop.run_forever()

    # ================================================================
    # MAVSDK CONNECTION & TELEMETRY
    # ================================================================

    async def _connect(self):
        await self.drone.connect(system_address=MAVSDK_ADDRESS)

        self.get_logger().info("Waiting for drone connection…")
        async for state in self.drone.core.connection_state():
            if state.is_connected:
                self.get_logger().info("Drone connected")
                break

        self.get_logger().info("Waiting for GPS fix and armable state…")
        async for health in self.drone.telemetry.health():
            if health.is_armable and health.is_global_position_ok:
                self._mav_ready = True
                self.get_logger().info("Drone ready")
                break

        # persistent telemetry streams
        asyncio.create_task(self._battery_stream())
        asyncio.create_task(self._altitude_stream())
        asyncio.create_task(self._attitude_stream())

    async def _battery_stream(self):
        async for b in self.drone.telemetry.battery():
            self.battery = b.remaining_percent
            self.battery_pub.publish(Float32(data=b.remaining_percent * 100.0))

    async def _altitude_stream(self):
        async for pos in self.drone.telemetry.position():
            self.alt_pub.publish(Float32(data=pos.relative_altitude_m))

    async def _attitude_stream(self):
        async for att in self.drone.telemetry.attitude_euler():
            self.att_pub.publish(
                Vector3(x=att.roll_deg, y=att.pitch_deg, z=att.yaw_deg)
            )

    # ================================================================
    # ACTION SERVER CALLBACKS
    # ================================================================

    def goal_callback(self, goal_request):
        """Reject new goals while a mission is already active."""
        if self._active_goal_handle is not None:
            self.get_logger().warn("Mission already active — rejecting new goal")
            return GoalResponse.REJECT

        # Validate waypoints
        if not goal_request.waypoints:
            self.get_logger().error("Goal rejected: empty waypoint list")
            return GoalResponse.REJECT

        for i, wp in enumerate(goal_request.waypoints):
            if wp.servo_index not in VALID_SERVO_INDICES:
                self.get_logger().error(
                    f"Goal rejected: waypoint {i} has invalid servo_index "
                    f"{wp.servo_index} (must be 0–6)"
                )
                return GoalResponse.REJECT

        self.get_logger().info(
            f"Accepting goal with {len(goal_request.waypoints)} waypoint(s)"
        )
        return GoalResponse.ACCEPT

    def cancel_callback(self, goal_handle):
        self.get_logger().info("Cancel requested for multi-delivery mission")
        self._cancel_requested = True
        return CancelResponse.ACCEPT

    def execute_callback(self, goal_handle):
        """Bridge synchronous ROS 2 callback to async mission coroutine."""
        self._active_goal_handle = goal_handle
        self._cancel_requested   = False

        waypoints = goal_handle.request.waypoints
        self.get_logger().info(
            f"Executing multi-delivery: {len(waypoints)} waypoint(s)"
        )

        future = asyncio.run_coroutine_threadsafe(
            self._mission(goal_handle, waypoints),
            self.loop,
        )

        result = MultiDeliveryActionTrigger.Result()
        try:
            future.result()
            goal_handle.succeed()
            result.success = 1.0
            self.missions_completed += 1
            self.mission_pub.publish(String(data=str(self.missions_completed)))
            self.get_logger().info(
                f"Multi-delivery complete. Total missions: {self.missions_completed}, "
                f"Total payloads: {self.payloads_delivered}"
            )
        except asyncio.CancelledError:
            self.get_logger().warn("Mission coroutine cancelled")
            goal_handle.canceled()
            result.success = 0.0
        except Exception as exc:
            self.get_logger().error(f"Mission failed: {exc}")
            goal_handle.abort()
            result.success = -1.0
        finally:
            self._active_goal_handle = None
            self._publish_state("Standby")

        return result

    # ================================================================
    # MISSION COROUTINE
    # ================================================================

    async def _mission(self, goal_handle, waypoints):
        """
        Full multi-waypoint delivery mission:
          1. Wait for drone readiness + pre-flight battery check
          2. Arm + takeoff
          3. Capture home position + start offboard mode
          4. For each waypoint:
               a. Fly to waypoint (with cancel / battery / timeout guards)
               b. Hold HOLD_TIME_SEC
               c. Call /servo/release with waypoint.servo_index
               d. Hold POST_DROP_HOLD_SEC
          5. Stop offboard → RTL → wait for landing
        """

        total = len(waypoints)

        # ---- 1. Pre-flight ----
        self._publish_state("Waiting for drone")
        while not self._mav_ready:
            await asyncio.sleep(0.2)

        if self.battery < BATTERY_RTL_THRESHOLD:
            raise RuntimeError(
                f"Battery too low for mission: {self.battery * 100:.1f}%"
            )

        # ---- 2. Arm + takeoff ----
        self._publish_state("Arming")
        await self.drone.action.arm()

        self._publish_state("Taking off")
        await self.drone.action.takeoff()
        await asyncio.sleep(TAKEOFF_WAIT_SEC)

        # Capture home position
        async for home in self.drone.telemetry.home():
            home_lat = home.latitude_deg
            home_lon = home.longitude_deg
            break

        # ---- 3. Start offboard ----
        self._publish_state("Starting offboard")
        first_wp = waypoints[0]
        first_alt = first_wp.altitude if first_wp.altitude > 0.0 else CRUISE_ALT_M
        first_n, first_e = gps_to_ned(home_lat, home_lon, first_wp.latitude, first_wp.longitude)
        await self._start_offboard(first_n, first_e, first_alt)

        mission_start = time.time()

        # ---- 4. Visit each waypoint ----
        for wp_idx, wp in enumerate(waypoints):

            tgt_lat  = wp.latitude
            tgt_lon  = wp.longitude
            tgt_alt  = wp.altitude if wp.altitude > 0.0 else CRUISE_ALT_M
            servo_idx = int(wp.servo_index)

            tgt_north, tgt_east = gps_to_ned(home_lat, home_lon, tgt_lat, tgt_lon)

            self._publish_state(f"Flying to waypoint {wp_idx + 1}/{total}")
            self.wp_pub.publish(String(data=f"{wp_idx + 1}/{total}"))
            self.get_logger().info(
                f"[WP {wp_idx + 1}/{total}] Flying to "
                f"({tgt_lat:.6f}, {tgt_lon:.6f}) alt={tgt_alt:.1f}m "
                f"servo={servo_idx}"
            )

            yaw = 0.0

            # ---- 4a. Fly to waypoint ----
            while True:
                elapsed = time.time() - mission_start

                if self._cancel_requested:
                    self.get_logger().warn(f"Cancel during fly to WP {wp_idx + 1} — RTL")
                    await self._safe_rtl()
                    return

                if self.battery < BATTERY_RTL_THRESHOLD:
                    self.get_logger().error(
                        f"Battery critical ({self.battery * 100:.1f}%) at WP {wp_idx + 1} — RTL"
                    )
                    await self._safe_rtl()
                    raise RuntimeError("Battery critical during flight")

                if elapsed > MAX_MISSION_TIME_SEC:
                    self.get_logger().error("Mission timeout — RTL")
                    await self._safe_rtl()
                    raise RuntimeError("Mission timed out")

                # current GPS
                curr_lat, curr_lon = await self._current_gps()
                curr_alt_m         = await self._current_alt()

                # publish feedback
                dist = haversine(curr_lat, curr_lon, tgt_lat, tgt_lon)
                await self._publish_feedback(
                    goal_handle, wp_idx, total,
                    curr_lat, curr_lon, curr_alt_m, dist
                )

                yaw = bearing_deg(curr_lat, curr_lon, tgt_lat, tgt_lon)

                if dist <= ARRIVAL_RADIUS_M:
                    self.get_logger().info(
                        f"[WP {wp_idx + 1}] Arrived (dist={dist:.2f}m)"
                    )
                    break

                await self.drone.offboard.set_position_ned(
                    PositionNedYaw(tgt_north, tgt_east, -tgt_alt, yaw)
                )
                await asyncio.sleep(1.0 / SETPOINT_RATE_HZ)

            # ---- 4b. Hold before drop ----
            self._publish_state(f"Holding at waypoint {wp_idx + 1}/{total}")
            self.get_logger().info(
                f"[WP {wp_idx + 1}] Holding for {HOLD_TIME_SEC}s before drop"
            )
            await self._hold(
                goal_handle, wp_idx, total,
                tgt_north, tgt_east, tgt_alt, yaw,
                HOLD_TIME_SEC, mission_start
            )

            # ---- 4c. Trigger servo release ----
            self._publish_state(
                f"Releasing servo {servo_idx} at waypoint {wp_idx + 1}/{total}"
            )
            success = await self._trigger_servo(servo_idx)

            if success:
                self.payloads_delivered += 1
                self.payload_pub.publish(String(data=str(self.payloads_delivered)))
                self.get_logger().info(
                    f"[WP {wp_idx + 1}] Servo {servo_idx} released — "
                    f"total payloads delivered: {self.payloads_delivered}"
                )
            else:
                self.get_logger().error(
                    f"[WP {wp_idx + 1}] Servo {servo_idx} release FAILED — "
                    f"continuing to next waypoint"
                )

            # ---- 4d. Hold after drop ----
            self.get_logger().info(
                f"[WP {wp_idx + 1}] Post-drop hold for {POST_DROP_HOLD_SEC}s"
            )
            await self._hold(
                goal_handle, wp_idx, total,
                tgt_north, tgt_east, tgt_alt, yaw,
                POST_DROP_HOLD_SEC, mission_start
            )

        # ---- 5. All waypoints done — RTL ----
        self.get_logger().info("All waypoints completed — returning to launch")
        await self._safe_rtl()

    # ================================================================
    # SERVO RELEASE
    # ================================================================

    async def _trigger_servo(self, servo_index: int) -> bool:
        """
        Call the /servo/release service with the given index (0–6).
        Returns True on success, False on failure or timeout.
        """
        if servo_index not in VALID_SERVO_INDICES:
            self.get_logger().error(
                f"Invalid servo index {servo_index} — must be 0–6. Skipping."
            )
            return False

        # Wait for service to be available
        if not self.servo_client.wait_for_service(timeout_sec=SERVO_TIMEOUT_SEC):
            self.get_logger().error(
                f"Servo release service /servo/release not available "
                f"after {SERVO_TIMEOUT_SEC}s"
            )
            return False

        request = ServoRelease.Request()
        request.servo_index = servo_index

        self.get_logger().info(f"Calling /servo/release with index={servo_index}")

        try:
            # Bridge async ROS 2 service call into the asyncio loop
            future = self.servo_client.call_async(request)

            # Poll until done (non-blocking sleep to keep setpoints alive)
            deadline = time.time() + SERVO_TIMEOUT_SEC
            while not future.done():
                if time.time() > deadline:
                    self.get_logger().error(
                        f"Servo service call timed out after {SERVO_TIMEOUT_SEC}s"
                    )
                    return False
                await asyncio.sleep(0.05)

            response = future.result()
            if response.success:
                self.get_logger().info(
                    f"Servo {servo_index} released: {response.message}"
                )
                return True
            else:
                self.get_logger().error(
                    f"Servo {servo_index} release failed: {response.message}"
                )
                return False

        except Exception as exc:
            self.get_logger().error(f"Servo service call exception: {exc}")
            return False

    # ================================================================
    # HELPERS
    # ================================================================

    async def _start_offboard(self, north: float, east: float, alt: float):
        """
        Seed PX4 with setpoints then enable offboard mode.
        PX4 requires at least a few setpoints before accepting offboard.
        """
        for _ in range(10):
            await self.drone.offboard.set_position_ned(
                PositionNedYaw(north, east, -alt, 0.0)
            )
            await asyncio.sleep(0.1)

        try:
            await self.drone.offboard.start()
            self.get_logger().info("Offboard mode started")
        except OffboardError as exc:
            raise RuntimeError(f"Failed to start offboard mode: {exc}") from exc

    async def _hold(
        self,
        goal_handle,
        wp_idx: int,
        total: int,
        north: float,
        east: float,
        alt: float,
        yaw: float,
        duration_sec: float,
        mission_start: float,
    ):
        """
        Maintain position for `duration_sec` while still checking guards
        and publishing feedback. Keeps the offboard heartbeat alive.
        """
        iterations = int(duration_sec * SETPOINT_RATE_HZ)
        curr_lat, curr_lon = await self._current_gps()
        curr_alt_m         = await self._current_alt()

        for _ in range(iterations):
            if self._cancel_requested:
                await self._safe_rtl()
                return

            if self.battery < BATTERY_RTL_THRESHOLD:
                await self._safe_rtl()
                raise RuntimeError("Battery critical during hold")

            if time.time() - mission_start > MAX_MISSION_TIME_SEC:
                await self._safe_rtl()
                raise RuntimeError("Mission timed out during hold")

            await self._publish_feedback(
                goal_handle, wp_idx, total,
                curr_lat, curr_lon, curr_alt_m, 0.0
            )

            await self.drone.offboard.set_position_ned(
                PositionNedYaw(north, east, -alt, yaw)
            )
            await asyncio.sleep(1.0 / SETPOINT_RATE_HZ)

    async def _safe_rtl(self):
        """Stop offboard cleanly, issue RTL, wait for landing."""
        self._publish_state("Returning to Launch")
        try:
            await self.drone.offboard.stop()
        except Exception:
            pass  # offboard may already be inactive

        await self.drone.action.return_to_launch()

        async for in_air in self.drone.telemetry.in_air():
            if not in_air:
                break

        self._publish_state("Landed")

    async def _current_gps(self) -> tuple[float, float]:
        """Single-sample current latitude and longitude."""
        async for pos in self.drone.telemetry.position():
            return pos.latitude_deg, pos.longitude_deg

    async def _current_alt(self) -> float:
        """Single-sample current relative altitude (m)."""
        async for pos in self.drone.telemetry.position():
            return pos.relative_altitude_m

    async def _publish_feedback(
        self,
        goal_handle,
        wp_idx: int,
        total: int,
        curr_lat: float,
        curr_lon: float,
        curr_alt: float,
        dist: float,
    ):
        feedback = MultiDeliveryActionTrigger.Feedback()
        feedback.waypoint_index    = wp_idx
        feedback.total_waypoints   = total
        feedback.current_lat       = curr_lat
        feedback.current_lon       = curr_lon
        feedback.current_alt       = curr_alt
        feedback.distance_to_next  = dist
        goal_handle.publish_feedback(feedback)

    def _publish_state(self, state: str):
        self.state_pub.publish(String(data=state))
        self.get_logger().info(f"[State] {state}")


# ================================================================
# ENTRY POINT
# ================================================================

def main(args=None):
    rclpy.init(args=args)
    node = MultiDeliveryOffboardManager()
    executor = MultiThreadedExecutor()
    try:
        rclpy.spin(node, executor)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
