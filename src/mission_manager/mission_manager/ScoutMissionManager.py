#!/usr/bin/env python3

import rclpy
import asyncio
import threading
import time
import math

from rclpy.node import Node
from rclpy.action import ActionServer, GoalResponse, CancelResponse
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import ReentrantCallbackGroup

from std_msgs.msg import Float32, String
from geometry_msgs.msg import Polygon as RosPolygon, Point32, Vector3
from geographic_msgs.msg import GeoPoint

from mission_interfaces.srv import GetMissionBoundary
from mission_interfaces.action import ScoutActionTrigger

from mavsdk import System
from mavsdk.mission import MissionItem, MissionPlan
from mavsdk.geofence import Point, Polygon as MavsdkPolygon, FenceType, GeofenceData


# ================= SAFETY CONSTANTS =================
BATTERY_RTL_THRESHOLD = 0.30
MAX_MISSION_TIME_SEC = 900


class ScoutMissionManager(Node):

    def __init__(self):
        super().__init__('scout_mission_manager')
        self.get_logger().info("Scout Mission Manager started (SAFE MODE)")

        self.cb_group = ReentrantCallbackGroup()

        # -------- STATE --------
        self._active_goal = None
        self._cancel_requested = False
        self.battery = 1.0
        self.mission_start_time = None

        # -------- TELEMETRY PUBLISHERS --------
        self.state_pub = self.create_publisher(String, '/scout_drone/state', 10)
        self.battery_pub = self.create_publisher(Float32, '/scout_drone/battery', 10)
        self.alt_pub = self.create_publisher(Float32, '/scout_drone/altitude', 10)
        self.att_pub = self.create_publisher(Vector3, '/scout_drone/attitude', 10)

        self._publish_state("Standby")

        # -------- SERVICE CLIENT --------
        self.boundary_client = self.create_client(
            GetMissionBoundary,
            'get_mission_boundary',
            callback_group=self.cb_group
        )

        # -------- GEOFENCE VIS --------
        self.fence_pub = self.create_publisher(RosPolygon, 'mission_geofence', 10)

        # -------- MAVSDK --------
        self.loop = asyncio.new_event_loop()
        threading.Thread(target=self._run_loop, daemon=True).start()

        self.drone = System()
        asyncio.run_coroutine_threadsafe(self._connect(), self.loop)

        # -------- ACTION SERVER --------
        self.action_server = ActionServer(
            self,
            ScoutActionTrigger,
            'start_scan',
            execute_callback=self.execute_callback,
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback,
            callback_group=self.cb_group
        )

    # =====================================================
    def _run_loop(self):
        asyncio.set_event_loop(self.loop)
        self.loop.run_forever()

    async def _connect(self):
        await self.drone.connect(system_address="udp://:14540")

        async for health in self.drone.telemetry.health():
            if health.is_global_position_ok and health.is_armable:
                break

        asyncio.create_task(self._telemetry_monitor())
        self.get_logger().info("Scout drone connected")

    async def _telemetry_monitor(self):
        asyncio.create_task(self._battery_stream())
        asyncio.create_task(self._altitude_stream())
        asyncio.create_task(self._attitude_stream())

    async def _battery_stream(self):
        async for b in self.drone.telemetry.battery():
            self.battery = b.remaining_percent
            self.battery_pub.publish(Float32(data=b.remaining_percent * 100))

    async def _altitude_stream(self):
        async for pos in self.drone.telemetry.position():
            self.alt_pub.publish(Float32(data=pos.relative_altitude_m))

    async def _attitude_stream(self):
      async for att in self.drone.telemetry.attitude_euler():
        self.att_pub.publish(Vector3(
            x=att.roll_deg,
            y=att.pitch_deg,
            z=att.yaw_deg
         ))

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
            goal_handle.succeed()
            result.success = "Mission completed and RTL successful"
        except Exception as e:
            self.get_logger().error(str(e))
            goal_handle.abort()
            result.success = str(e)
        finally:
            self._active_goal = None

        return result

    async def _execute_async(self, goal_handle):

        self._publish_state("Preparing mission")

        boundary = await self._request_boundary_service()
        await self._upload_geofence(boundary)
        await self._upload_mission(goal_handle.request.waypoints)

        await self.drone.action.arm()
        await self.drone.mission.start_mission()

        self.mission_start_time = time.time()
        self._publish_state("Scanning")

        await self._monitor_mission()

    # =====================================================
    async def _request_boundary_service(self):
        while not self.boundary_client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info("Waiting for boundary service...")

        resp = await self.boundary_client.call_async(
            GetMissionBoundary.Request()
        )

        if not resp.success:
            raise RuntimeError("Boundary service failed")

        return resp.boundary_points

    async def _upload_geofence(self, points):

        mav_pts = [Point(p.latitude, p.longitude) for p in points]
        mav_pts.append(mav_pts[0])

        ros_poly = RosPolygon()
        for p in points:
            ros_poly.points.append(Point32(x=p.latitude, y=p.longitude))
        ros_poly.points.append(ros_poly.points[0])
        self.fence_pub.publish(ros_poly)

        await self.drone.geofence.clear_geofence()
        await self.drone.geofence.upload_geofence(
            GeofenceData(
                polygons=[MavsdkPolygon(mav_pts, FenceType.INCLUSION)],
                circles=[]
            )
        )

    async def _upload_mission(self, waypoints):

        items = []
        for wp in waypoints:
            items.append(
                MissionItem(
                    wp.latitude,
                    wp.longitude,
                    wp.altitude,
                    3.0,
                    True,
                    float("nan"),
                    float("nan"),
                    MissionItem.CameraAction.NONE,
                    *[float("nan")] * 5,
                    MissionItem.VehicleAction.NONE
                )
            )

        await self.drone.mission.upload_mission(MissionPlan(items))

    # =====================================================
    async def _monitor_mission(self):

        self.get_logger().info("Monitoring mission progress...")

        async for progress in self.drone.mission.mission_progress():

            if self._cancel_requested:
                await self.drone.action.return_to_launch()
                raise RuntimeError("Mission cancelled")

            if self.battery < BATTERY_RTL_THRESHOLD:
                await self.drone.action.return_to_launch()
                raise RuntimeError("Battery low – RTL triggered")

            if time.time() - self.mission_start_time > MAX_MISSION_TIME_SEC:
                await self.drone.action.return_to_launch()
                raise RuntimeError("Mission timeout – RTL triggered")

            self.get_logger().info(
                f"Mission progress: {progress.current}/{progress.total}"
            )

            if progress.current == progress.total:
                self.get_logger().info("All waypoints completed")
                break

        while not await self.drone.mission.is_mission_finished():
            await asyncio.sleep(1)

        self._publish_state("Returning to Launch")
        await self.drone.action.return_to_launch()

        async for in_air in self.drone.telemetry.in_air():
            if not in_air:
                break

        self._publish_state("Mission Completed")

    # =====================================================
    def goal_callback(self, goal):
        return GoalResponse.ACCEPT if self._active_goal is None else GoalResponse.REJECT

    def cancel_callback(self, goal_handle):
        self._cancel_requested = True
        return CancelResponse.ACCEPT

    def _publish_state(self, state):
        self.state_pub.publish(String(data=state))


# =========================================================
def main(args=None):
    rclpy.init(args=args)
    node = ScoutMissionManager()
    executor = MultiThreadedExecutor()

    try:
        rclpy.spin(node, executor)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()