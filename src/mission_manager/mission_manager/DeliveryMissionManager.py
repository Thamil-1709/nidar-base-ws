#!/usr/bin/env python3

import rclpy
import asyncio
import threading
import time
import math
from collections import deque

from rclpy.node import Node
from rclpy.action import ActionServer, GoalResponse, CancelResponse
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import ReentrantCallbackGroup

from std_msgs.msg import String, Float32
from geometry_msgs.msg import Vector3

from mavsdk import System
from mavsdk.offboard import OffboardError, PositionNedYaw
from mission_interfaces.action import DeliveryActionTrigger


# ================= CONFIG =================
CRUISE_ALT_M          = 10.0       # Default cruise altitude (m, relative)
SETPOINT_RATE_HZ      = 10         # Offboard setpoint frequency
ARRIVAL_RADIUS_M      = 2.0        # Distance threshold to consider arrived (m)
HOLD_TIME_SEC         = 4          # Time to hover over target before RTL (s)
BATTERY_RTL_THRESHOLD = 0.25       # Minimum battery fraction before forced RTL
MAX_MISSION_TIME_SEC  = 600        # Hard timeout for entire delivery mission (s)
TAKEOFF_WAIT_SEC      = 5          # Seconds to wait after takeoff command
MAVSDK_ADDRESS        = "udp://:14540"


# ================= UTILS =================

def haversine(lat1: float, lon1: float, lat2: float, lon2: float) -> float:
    """Return great-circle distance in metres between two GPS points."""
    R = 6_371_000.0
    p1, p2 = math.radians(lat1), math.radians(lat2)
    dp = math.radians(lat2 - lat1)
    dl = math.radians(lon2 - lon1)
    a = math.sin(dp / 2) ** 2 + math.cos(p1) * math.cos(p2) * math.sin(dl / 2) ** 2
    return 2 * R * math.atan2(math.sqrt(a), math.sqrt(1 - a))


def bearing_deg(lat1: float, lon1: float, lat2: float, lon2: float) -> float:
    """Return initial bearing (degrees, 0–360) from point 1 to point 2."""
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
    """Convert GPS coordinate to NED (North, East) offsets in metres from home."""
    north = haversine(home_lat, home_lon, lat, home_lon)
    east  = haversine(home_lat, home_lon, home_lat, lon)
    if lat < home_lat:
        north *= -1
    if lon < home_lon:
        east *= -1
    return north, east


# ================= NODE =================

class DeliveryOffboardManager(Node):
    """
    ROS 2 action server that accepts delivery goals from MissionManager,
    flies the delivery drone to the target GPS location using MAVSDK offboard
    mode, hovers for HOLD_TIME_SEC, then returns to launch.

    Fixes applied vs original:
      - Goal request is correctly read from goal_handle.request (not raw queue)
      - Battery is continuously monitored via a persistent async stream
      - Battery is checked mid-flight and triggers RTL if threshold is breached
      - Mission timeout (MAX_MISSION_TIME_SEC) added
      - Cancel is checked during the hold phase as well as the fly phase
      - Offboard mode is stopped cleanly before any RTL / abort
      - Delivery telemetry (battery, altitude, attitude) is published to ROS topics
      - DeliveryCompletedCount is tracked and published
      - Goal queue is only used for ordering; goal data always comes from goal_handle
      - Comprehensive state publishing throughout the mission lifecycle
    """

    def __init__(self):
        super().__init__("delivery_offboard_manager")
        self.get_logger().info("Delivery Offboard Manager starting…")

        # ---------- internal state ----------
        self._active_goal_handle = None
        self._cancel_requested   = False
        self._mav_ready          = False
        self.battery             = 1.0          # fraction 0–1, continuously updated
        self.delivery_completed  = 0

        # ---------- publishers ----------
        self.state_pub   = self.create_publisher(String,  "/delivery/state",    10)
        self.battery_pub = self.create_publisher(Float32, "/delivery/battery",  10)
        self.alt_pub     = self.create_publisher(Float32, "/delivery/altitude",  10)
        self.att_pub     = self.create_publisher(Vector3, "/delivery/attitude",  10)
        self.count_pub   = self.create_publisher(String,  "/delivery/completed_count", 10)

        self._publish_state("Standby")

        # ---------- async event loop in dedicated thread ----------
        self.loop = asyncio.new_event_loop()
        threading.Thread(target=self._run_loop, daemon=True).start()

        # ---------- MAVSDK ----------
        self.drone = System()
        asyncio.run_coroutine_threadsafe(self._connect(), self.loop)

        # ---------- action server ----------
        self.action_server = ActionServer(
            self,
            DeliveryActionTrigger,
            "start_delivery",
            execute_callback=self.execute_callback,
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback,
            callback_group=ReentrantCallbackGroup(),
        )

        self.get_logger().info("Delivery Offboard Manager ready")

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
        """Connect to the drone and wait until it is armable."""
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

        # Launch persistent telemetry streams
        asyncio.create_task(self._battery_stream())
        asyncio.create_task(self._altitude_stream())
        asyncio.create_task(self._attitude_stream())

    async def _battery_stream(self):
        """
        Continuously update self.battery so the mission loop always has a
        fresh reading. Also publishes to /delivery/battery (percentage 0–100).
        """
        async for b in self.drone.telemetry.battery():
            self.battery = b.remaining_percent
            self.battery_pub.publish(Float32(data=b.remaining_percent * 100.0))

    async def _altitude_stream(self):
        """Publish relative altitude to /delivery/altitude (metres)."""
        async for pos in self.drone.telemetry.position():
            self.alt_pub.publish(Float32(data=pos.relative_altitude_m))

    async def _attitude_stream(self):
        """Publish roll/pitch/yaw to /delivery/attitude (degrees)."""
        async for att in self.drone.telemetry.attitude_euler():
            self.att_pub.publish(
                Vector3(x=att.roll_deg, y=att.pitch_deg, z=att.yaw_deg)
            )

    # ================================================================
    # ACTION SERVER CALLBACKS
    # ================================================================

    def goal_callback(self, goal_request):
        """
        Accept new goals only when no mission is active.
        Reject incoming goals while a delivery is in progress so that
        MissionManager's delivery_busy flag stays consistent.
        """
        if self._active_goal_handle is not None:
            self.get_logger().warn("Delivery already active — rejecting new goal")
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def cancel_callback(self, goal_handle):
        self.get_logger().info("Cancel requested for delivery mission")
        self._cancel_requested = True
        return CancelResponse.ACCEPT

    def execute_callback(self, goal_handle):
        """
        Bridge between the synchronous ROS 2 action server and the async
        MAVSDK mission coroutine. Runs the mission and maps success/failure
        to the appropriate action result.
        """
        self._active_goal_handle = goal_handle
        self._cancel_requested   = False

        # ---- extract goal data here, once, from the correct attribute ----
        goal_request = goal_handle.request          # DeliveryActionTrigger.Goal
        target_lat   = goal_request.latitude
        target_lon   = goal_request.longitude
        # Use goal altitude if non-zero, otherwise fall back to cruise altitude
        target_alt   = goal_request.altitude \
                       if goal_request.altitude > 0.0 \
                       else CRUISE_ALT_M

        self.get_logger().info(
            f"Executing delivery to ({target_lat:.6f}, {target_lon:.6f}) "
            f"alt={target_alt:.1f}m"
        )

        future = asyncio.run_coroutine_threadsafe(
            self._mission(goal_handle, target_lat, target_lon, target_alt),
            self.loop,
        )

        result = DeliveryActionTrigger.Result()
        try:
            future.result()                         # blocks until coroutine finishes
            goal_handle.succeed()
            result.success = 1.0
            self.delivery_completed += 1
            self.count_pub.publish(String(data=str(self.delivery_completed)))
            self.get_logger().info(
                f"Delivery complete. Total deliveries: {self.delivery_completed}"
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

    async def _mission(
        self,
        goal_handle,
        target_lat: float,
        target_lon: float,
        target_alt: float,
    ):
        """
        Full delivery mission:
          1. Wait for drone readiness
          2. Pre-flight battery check
          3. Arm + takeoff
          4. Start offboard mode
          5. Fly to target in a control loop with cancel + battery + timeout guards
          6. Hold over target (with same guards)
          7. Stop offboard + RTL
        """

        # ---- 1. Wait for drone ready ----
        self._publish_state("Waiting for drone")
        while not self._mav_ready:
            await asyncio.sleep(0.2)

        # ---- 2. Pre-flight battery check ----
        if self.battery < BATTERY_RTL_THRESHOLD:
            raise RuntimeError(
                f"Battery too low for delivery: {self.battery * 100:.1f}%"
            )

        # ---- 3. Arm and takeoff ----
        self._publish_state("Arming")
        await self.drone.action.arm()

        self._publish_state("Taking off")
        await self.drone.action.takeoff()
        await asyncio.sleep(TAKEOFF_WAIT_SEC)

        # Capture home position immediately after takeoff
        async for home in self.drone.telemetry.home():
            home_lat = home.latitude_deg
            home_lon = home.longitude_deg
            break

        # Pre-compute fixed NED target (does not change during flight)
        tgt_north, tgt_east = gps_to_ned(home_lat, home_lon, target_lat, target_lon)

        # ---- 4. Start offboard mode ----
        self._publish_state("Starting offboard")
        await self._start_offboard(tgt_north, tgt_east, target_alt)

        mission_start = time.time()

        # ---- 5. Fly to target ----
        self._publish_state("Flying to target")
        yaw = 0.0   # initialised before loop; updated each iteration

        while True:
            # --- safety guards ---
            elapsed = time.time() - mission_start

            if self._cancel_requested:
                self.get_logger().warn("Cancel during fly phase — RTL")
                await self._safe_rtl()
                return

            if self.battery < BATTERY_RTL_THRESHOLD:
                self.get_logger().error(
                    f"Battery critical ({self.battery * 100:.1f}%) during flight — RTL"
                )
                await self._safe_rtl()
                raise RuntimeError("Battery critical during flight")

            if elapsed > MAX_MISSION_TIME_SEC:
                self.get_logger().error("Mission timeout — RTL")
                await self._safe_rtl()
                raise RuntimeError("Mission timed out")

            # --- publish feedback (actual .action fields: current_lat, current_lon, current_alt) ---
            curr_lat, curr_lon = await self._current_gps()
            async for _pos in self.drone.telemetry.position():
                curr_alt = _pos.relative_altitude_m
                break
            feedback = DeliveryActionTrigger.Feedback()
            feedback.current_lat = curr_lat
            feedback.current_lon = curr_lon
            feedback.current_alt = curr_alt
            goal_handle.publish_feedback(feedback)

            # --- arrival check (curr_lat/lon already fetched for feedback above) ---
            dist = haversine(curr_lat, curr_lon, target_lat, target_lon)
            yaw  = bearing_deg(curr_lat, curr_lon, target_lat, target_lon)

            if dist <= ARRIVAL_RADIUS_M:
                self.get_logger().info(f"Arrived at target (dist={dist:.2f}m)")
                break

            # --- send offboard setpoint ---
            await self.drone.offboard.set_position_ned(
                PositionNedYaw(tgt_north, tgt_east, -target_alt, yaw)
            )
            await asyncio.sleep(1.0 / SETPOINT_RATE_HZ)

        # ---- 6. Hold over target ----
        self._publish_state("Holding at target")
        hold_iterations = HOLD_TIME_SEC * SETPOINT_RATE_HZ

        for i in range(hold_iterations):
            # --- safety guards during hold ---
            if self._cancel_requested:
                self.get_logger().warn("Cancel during hold phase — RTL")
                await self._safe_rtl()
                return

            if self.battery < BATTERY_RTL_THRESHOLD:
                self.get_logger().error("Battery critical during hold — RTL")
                await self._safe_rtl()
                raise RuntimeError("Battery critical during hold")

            if time.time() - mission_start > MAX_MISSION_TIME_SEC:
                self.get_logger().error("Mission timeout during hold — RTL")
                await self._safe_rtl()
                raise RuntimeError("Mission timed out during hold")

            await self.drone.offboard.set_position_ned(
                PositionNedYaw(tgt_north, tgt_east, -target_alt, yaw)
            )
            await asyncio.sleep(1.0 / SETPOINT_RATE_HZ)

        # ---- 7. Return to launch ----
        await self._safe_rtl()

    # ================================================================
    # HELPERS
    # ================================================================

    async def _start_offboard(self, north: float, east: float, alt: float):
        """
        Send several setpoints at the current position before calling
        offboard.start() — required by PX4 to accept offboard mode.
        """
        for _ in range(10):
            await self.drone.offboard.set_position_ned(
                PositionNedYaw(north, east, -alt, 0.0)
            )
            await asyncio.sleep(0.1)

        try:
            await self.drone.offboard.start()
        except OffboardError as exc:
            raise RuntimeError(f"Failed to start offboard mode: {exc}") from exc

    async def _safe_rtl(self):
        """
        Stop offboard mode cleanly then issue return-to-launch.
        Waits until the drone has landed before returning.
        """
        self._publish_state("Returning to Launch")
        try:
            await self.drone.offboard.stop()
        except Exception:
            pass  # offboard may already be inactive; that is fine

        await self.drone.action.return_to_launch()

        # Wait for landing
        async for in_air in self.drone.telemetry.in_air():
            if not in_air:
                break

        self._publish_state("Landed")

    async def _current_gps(self) -> tuple[float, float]:
        """Return the current (latitude, longitude) from a single telemetry sample."""
        async for pos in self.drone.telemetry.position():
            return pos.latitude_deg, pos.longitude_deg

    def _publish_state(self, state: str):
        self.state_pub.publish(String(data=state))
        self.get_logger().info(f"[State] {state}")


# ================================================================
# ENTRY POINT
# ================================================================

def main(args=None):
    rclpy.init(args=args)
    node = DeliveryOffboardManager()
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
