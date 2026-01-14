#!/usr/bin/env python3

import rclpy
import asyncio
import threading

from rclpy.node import Node
from rclpy.action import ActionServer, GoalResponse, CancelResponse
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import ReentrantCallbackGroup

from mission_interfaces.srv import GetMissionBoundary
from mission_interfaces.action import ScoutActionTrigger

from geographic_msgs.msg import GeoPoint
from geometry_msgs.msg import Polygon as RosPolygon, Point32

from mavsdk import System
from mavsdk.mission import MissionItem, MissionPlan
from mavsdk.geofence import Point, Polygon as MavsdkPolygon, FenceType, GeofenceData


class ScoutMissionManager(Node):

    def __init__(self):
        super().__init__('scout_mission_manager')
        self.get_logger().info("Scout Mission Manager started")

        self.callback_group = ReentrantCallbackGroup()

        # -------- SERVICE CLIENT --------
        self.boundary_client = self.create_client(
            GetMissionBoundary,
            'get_mission_boundary',
            callback_group=self.callback_group
        )

        # -------- VISUALIZATION --------
        self.fence_pub = self.create_publisher(
            RosPolygon, 'mission_geofence', 10
        )

        # -------- STATE --------
        self._active_goal = None
        self._cancel_requested = False

        # -------- MAVSDK LOOP --------
        self.loop = asyncio.new_event_loop()
        threading.Thread(
            target=self._run_loop,
            daemon=True
        ).start()

        self.drone = System()
        asyncio.run_coroutine_threadsafe(
            self._connect_and_prepare(), self.loop
        )

        # -------- ACTION SERVER --------
        self.action_server = ActionServer(
            self,
            ScoutActionTrigger,
            'start_scan',
            execute_callback=self.execute_callback,
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback,
            callback_group=self.callback_group
        )

    # =====================================================
    # ASYNC EVENT LOOP
    # =====================================================

    def _run_loop(self):
        asyncio.set_event_loop(self.loop)
        self.loop.run_forever()

    async def _connect_and_prepare(self):
        await self.drone.connect(system_address="udp://:14540")
        async for health in self.drone.telemetry.health():
            if health.is_global_position_ok and health.is_armable:
                self.get_logger().info("Drone ready")
                break

    # =====================================================
    # ACTION EXECUTION (SYNC)
    # =====================================================

    def execute_callback(self, goal_handle):
        self._active_goal = goal_handle
        self._cancel_requested = False
        result = ScoutActionTrigger.Result()

        future = asyncio.run_coroutine_threadsafe(
            self._execute_async(goal_handle),
            self.loop
        )

        try:
            future.result()
            if self._cancel_requested:
                goal_handle.canceled()
                result.success = "Mission cancelled"
            else:
                goal_handle.succeed()
                result.success = "Mission completed"
        except Exception as e:
            self.get_logger().error(f"Mission failed: {e}")
            goal_handle.abort()
            result.success = str(e)

        self._active_goal = None
        return result

    # =====================================================
    # REAL MISSION LOGIC (ASYNC)
    # =====================================================

    async def _execute_async(self, goal_handle):
        self.get_logger().info("Requesting mission boundary")

        boundary_points = await self._request_boundary_service()

        await self._upload_geofence(boundary_points)
        await self._upload_mission(goal_handle.request.waypoints)

        self.get_logger().info("Arming vehicle")
        await self.drone.action.arm()

        self.get_logger().info("Starting mission")
        await self.drone.mission.start_mission()

        await self._monitor_mission(goal_handle)

    # =====================================================
    # SERVICE + MAVSDK HELPERS
    # =====================================================

    async def _request_boundary_service(self):
        while not self.boundary_client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info("Waiting for get_mission_boundary service...")

        req = GetMissionBoundary.Request()  # ✅ EMPTY REQUEST
        future = self.boundary_client.call_async(req)
        response = await future

        if not response.success:
            raise RuntimeError("Mission boundary not available")

        return response.boundary_points

    async def _get_home_position(self):
        async for home in self.drone.telemetry.home():
            return home.latitude_deg, home.longitude_deg

    async def _upload_geofence(self, boundary_points):
        if len(boundary_points) < 3:
            raise RuntimeError("Geofence needs at least 3 boundary points")

        # --- Get home ---
        home_lat, home_lon = await self._get_home_position()
        self.get_logger().info(f"Home: {home_lat}, {home_lon}")

        mav_points = []
        ros_polygon = RosPolygon()

        for p in boundary_points:
            mav_points.append(Point(p.latitude, p.longitude))

            rp = Point32()
            rp.x = float(p.latitude)
            rp.y = float(p.longitude)
            rp.z = 0.0
            ros_polygon.points.append(rp)

        # --- CLOSE THE POLYGON ---
        mav_points.append(Point(
            boundary_points[0].latitude,
            boundary_points[0].longitude
        ))

        rp = Point32()
        rp.x = boundary_points[0].latitude
        rp.y = boundary_points[0].longitude
        rp.z = 0.0
        ros_polygon.points.append(rp)

        # Publish for RViz
        self.fence_pub.publish(ros_polygon)

        polygon = MavsdkPolygon(
            points=mav_points,
            fence_type=FenceType.INCLUSION
        )

        geofence = GeofenceData(
            polygons=[polygon],
            circles=[]
        )

        # --- CLEAR OLD FENCE FIRST ---
        await self.drone.geofence.clear_geofence()

        # --- UPLOAD ---
        await self.drone.geofence.upload_geofence(geofence)

        self.get_logger().info("Geofence uploaded and accepted by PX4")

    async def _upload_mission(self, waypoints):
            mission_items = []

            for wp in waypoints:
                mission_items.append(
                    MissionItem(
                        wp.latitude,
                        wp.longitude,
                        wp.altitude,
                        2.0,
                        True,
                        float("nan"),
                        float("nan"),
                        MissionItem.CameraAction.NONE,
                        *[float("nan")] * 5,
                        MissionItem.VehicleAction.NONE
                    )
                )

            await self.drone.mission.upload_mission(
                MissionPlan(mission_items)
            )

    async def _monitor_mission(self, goal_handle):
        async for pos in self.drone.telemetry.position():
            if self._cancel_requested:
                await self.drone.mission.pause_mission()
                await self.drone.action.return_to_launch()
                return

            feedback = ScoutActionTrigger.Feedback()
            feedback.current_location = GeoPoint(
                latitude=pos.latitude_deg,
                longitude=pos.longitude_deg,
                altitude=pos.relative_altitude_m
            )

            goal_handle.publish_feedback(feedback)

            if await self.drone.mission.is_mission_finished():
                self.get_logger().info("Mission finished")
                await self.drone.action.return_to_launch()

                break

    # =====================================================
    # ROS CALLBACKS
    # =====================================================

    def goal_callback(self, goal_request):
        return GoalResponse.ACCEPT if self._active_goal is None else GoalResponse.REJECT

    def cancel_callback(self, goal_handle):
        self._cancel_requested = True
        return CancelResponse.ACCEPT


def main(args=None):
    rclpy.init(args=args)
    node = ScoutMissionManager()
    executor = MultiThreadedExecutor()

    try:
        rclpy.spin(node, executor=executor)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
