#!/usr/bin/env python3

import rclpy
import asyncio
import threading
from rclpy.node import Node
from rclpy.action import ActionServer, GoalResponse, CancelResponse

from mission_interfaces.action import ScoutActionTrigger
from geographic_msgs.msg import GeoPoint

from mavsdk import System
from mavsdk.mission import MissionItem, MissionPlan
from mavsdk.geofence import Point, Polygon, FenceType, GeofenceData, Circle


class ScoutMissionManager(Node):

    def __init__(self):
        super().__init__('scout_mission_manager')
        self.get_logger().info("Scout Mission Manager started")

        # ---------------- STATE ----------------
        self._active_goal = None
        self._cancel_requested = False
        self._mavsdk_ready = threading.Event()

        # ---------------- MAVSDK EVENT LOOP ----------------
        self.mavsdk_loop = asyncio.new_event_loop()
        self.mavsdk_thread = threading.Thread(
            target=self._run_mavsdk_loop,
            daemon=True
        )
        self.mavsdk_thread.start()

        self.drone = System()

        # Start connection safely
        asyncio.run_coroutine_threadsafe(
            self._connect_and_wait_for_telemetry(),
            self.mavsdk_loop
        )

        # ---------------- ACTION SERVER ----------------
        self.action_server = ActionServer(
            self,
            ScoutActionTrigger,
            'start_scan',
            execute_callback=self.execute_callback,
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback
        )

    # =====================================================
    # MAVSDK LOOP
    # =====================================================

    def _run_mavsdk_loop(self):
        asyncio.set_event_loop(self.mavsdk_loop)
        self.mavsdk_loop.run_forever()

    async def _connect_and_wait_for_telemetry(self):
        self.get_logger().info("Connecting to MAVSDK...")
        await self.drone.connect(system_address="serial:///dev/ttyAMA10:921600")

        async for state in self.drone.core.connection_state():
            if state.is_connected:
                self.get_logger().info("MAVSDK core connected")
                break

        # 🔴 CRITICAL: wait until telemetry plugin is usable
        async for _ in self.drone.telemetry.health():
            self.get_logger().info("Telemetry plugin initialized")
            self._mavsdk_ready.set()
            return

    # =====================================================
    # ACTION CALLBACKS
    # =====================================================

    def goal_callback(self, goal_request):
        if not goal_request.waypoints:
            self.get_logger().error("Rejected goal: empty waypoint list")
            return GoalResponse.REJECT

        if self._active_goal is not None:
            self.get_logger().warn("Rejected goal: mission already running")
            return GoalResponse.REJECT

        return GoalResponse.ACCEPT

    def cancel_callback(self, goal_handle):
        self.get_logger().warn("Cancel requested")
        self._cancel_requested = True
        return CancelResponse.ACCEPT

    def execute_callback(self, goal_handle):
        # ---------- BLOCK UNTIL MAVSDK IS READY ----------
        if not self._mavsdk_ready.wait(timeout=15):
            result = ScoutActionTrigger.Result()
            result.success = "Mission failed: MAVSDK not ready"
            goal_handle.abort()
            return result

        self.get_logger().info("Scout mission execution started")
        self._active_goal = goal_handle
        self._cancel_requested = False

        result = ScoutActionTrigger.Result()

        try:
            # Get home position
            home_lat, home_lon = asyncio.run_coroutine_threadsafe(
                self._get_home(),
                self.mavsdk_loop
            ).result()

            # Upload geofence
            asyncio.run_coroutine_threadsafe(
                self._upload_geofence(home_lat, home_lon),
                self.mavsdk_loop
            ).result()

            # Upload mission
            asyncio.run_coroutine_threadsafe(
                self._upload_mission(goal_handle.request.waypoints),
                self.mavsdk_loop
            ).result()

            # Arm & start mission
            asyncio.run_coroutine_threadsafe(
                self.drone.action.arm(),
                self.mavsdk_loop
            ).result()

            asyncio.run_coroutine_threadsafe(
                self.drone.mission.start_mission(),
                self.mavsdk_loop
            ).result()

            # Start feedback stream
            feedback_future = asyncio.run_coroutine_threadsafe(
                self._publish_feedback(goal_handle),
                self.mavsdk_loop
            )

            # Wait until landed
            asyncio.run_coroutine_threadsafe(
                self._wait_for_landing(),
                self.mavsdk_loop
            ).result()

            feedback_future.cancel()

            if self._cancel_requested:
                goal_handle.canceled()
                result.success = "Mission cancelled"
            else:
                goal_handle.succeed()
                result.success = "Scout mission completed successfully"

        except Exception as e:
            self.get_logger().error(f"Mission failed: {e}")
            asyncio.run_coroutine_threadsafe(
                self._abort(),
                self.mavsdk_loop
            )
            goal_handle.abort()
            result.success = f"Mission failed: {str(e)}"

        finally:
            self._active_goal = None
            self._cancel_requested = False

        return result

    # =====================================================
    # MAVSDK HELPERS
    # =====================================================

    async def _get_home(self):
        async for home in self.drone.telemetry.home():
            return home.latitude_deg, home.longitude_deg

    async def _upload_geofence(self, lat, lon):
        d = 0.0002  # ~22 m

        polygon = Polygon([
            Point(lat - d, lon - d),
            Point(lat + d, lon - d),
            Point(lat + d, lon + d),
            Point(lat - d, lon + d)
        ], FenceType.INCLUSION)

        dummy_circle = Circle(Point(0, 0), 0, FenceType.INCLUSION)

        await self.drone.geofence.upload_geofence(
            GeofenceData([polygon], [dummy_circle])
        )

    async def _upload_mission(self, waypoints):
        mission_items = []

        for wp in waypoints:
            mission_items.append(
                MissionItem(
                    wp.latitude,
                    wp.longitude,
                    wp.altitude,
                    10.0,
                    True,
                    float("nan"),
                    float("nan"),
                    MissionItem.CameraAction.NONE,
                    *[float("nan")] * 5,
                    MissionItem.VehicleAction.NONE
                )
            )

        await self.drone.mission.set_return_to_launch_after_mission(True)
        await self.drone.mission.upload_mission(
            MissionPlan(mission_items)
        )

    async def _publish_feedback(self, goal_handle):
        async for pos in self.drone.telemetry.position():
            if self._cancel_requested:
                return

            feedback = ScoutActionTrigger.Feedback()
            feedback.current_location = GeoPoint(
                latitude=pos.latitude_deg,
                longitude=pos.longitude_deg,
                altitude=pos.absolute_altitude_m
            )
            goal_handle.publish_feedback(feedback)

    async def _abort(self):
        try:
            await self.drone.action.hold()
        except Exception:
            pass

    async def _wait_for_landing(self):
        async for in_air in self.drone.telemetry.in_air():
            if not in_air:
                return


def main(args=None):
    rclpy.init(args=args)
    node = ScoutMissionManager()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
