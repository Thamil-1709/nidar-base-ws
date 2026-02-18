#!/usr/bin/env python3

import rclpy
import asyncio
import threading
import math
from collections import deque

from rclpy.node import Node
from rclpy.action import ActionServer, GoalResponse, CancelResponse
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import ReentrantCallbackGroup

from std_msgs.msg import String, Float32
from mavsdk import System
from mavsdk.offboard import OffboardError, PositionNedYaw
from mission_interfaces.action import DeliveryActionTrigger

# ================= CONFIG =================
CRUISE_ALT_M = 10.0
SETPOINT_RATE_HZ = 10
ARRIVAL_RADIUS_M = 2.0
HOLD_TIME_SEC = 4
BATTERY_RTL_THRESHOLD = 0.25

# ================= UTILS =================
def haversine(lat1, lon1, lat2, lon2):
    R = 6371000.0
    p1, p2 = math.radians(lat1), math.radians(lat2)
    dp = math.radians(lat2 - lat1)
    dl = math.radians(lon2 - lon1)
    a = math.sin(dp/2)**2 + math.cos(p1)*math.cos(p2)*math.sin(dl/2)**2
    return 2 * R * math.atan2(math.sqrt(a), math.sqrt(1 - a))

def bearing_deg(lat1, lon1, lat2, lon2):
    y = math.sin(math.radians(lon2 - lon1)) * math.cos(math.radians(lat2))
    x = math.cos(math.radians(lat1))*math.sin(math.radians(lat2)) - \
        math.sin(math.radians(lat1))*math.cos(math.radians(lat2))* \
        math.cos(math.radians(lon2 - lon1))
    return (math.degrees(math.atan2(y, x)) + 360) % 360

def gps_to_ned(home_lat, home_lon, lat, lon):
    north = haversine(home_lat, home_lon, lat, home_lon)
    east  = haversine(home_lat, home_lon, home_lat, lon)
    if lat < home_lat: north *= -1
    if lon < home_lon: east *= -1
    return north, east

# ================= NODE =================
class DeliveryOffboardManager(Node):

    def __init__(self):
        super().__init__('delivery_offboard_manager')

        self.queue = deque()
        self.cancel_requested = False
        self.mav_ready = False
        self.battery = 1.0

        self.state_pub = self.create_publisher(String, '/delivery/state', 10)

        self.loop = asyncio.new_event_loop()
        threading.Thread(target=self._run_loop, daemon=True).start()

        self.drone = System()
        asyncio.run_coroutine_threadsafe(self._connect(), self.loop)

        self.action_server = ActionServer(
            self,
            DeliveryActionTrigger,
            'start_delivery',
            execute_callback=self.execute_callback,
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback,
            callback_group=ReentrantCallbackGroup()
        )

    def _run_loop(self):
        asyncio.set_event_loop(self.loop)
        self.loop.run_forever()

    async def _connect(self):
        await self.drone.connect(system_address="udp://:14540")

        async for state in self.drone.core.connection_state():
            if state.is_connected:
                break

        async for health in self.drone.telemetry.health():
            if health.is_armable and health.is_global_position_ok:
                self.mav_ready = True
                break

        async for b in self.drone.telemetry.battery():
            self.battery = b.remaining_percent

    # ============== ACTION ==============
    def goal_callback(self, goal):
        self.queue.append(goal)
        return GoalResponse.ACCEPT

    def cancel_callback(self, goal_handle):
        self.cancel_requested = True
        return CancelResponse.ACCEPT

    def execute_callback(self, goal_handle):
        future = asyncio.run_coroutine_threadsafe(
            self._mission(), self.loop
        )
        try:
            future.result()
            goal_handle.succeed()
            res = DeliveryActionTrigger.Result()
            res.success = 1.0
            return res
        except Exception as e:
            self.get_logger().error(str(e))
            goal_handle.abort()
            res = DeliveryActionTrigger.Result()
            res.success = -1.0
            return res

    # ============== MISSION ==============
    async def _mission(self):
        while not self.mav_ready:
            await asyncio.sleep(0.2)

        if self.battery < BATTERY_RTL_THRESHOLD:
            raise RuntimeError("Battery too low")

        await self.drone.action.arm()
        await self.drone.action.takeoff()
        await asyncio.sleep(5)

        # Home position
        async for home in self.drone.telemetry.home():
            home_lat, home_lon = home.latitude_deg, home.longitude_deg
            break

        await self._start_offboard()

        goal = self.queue.popleft()
        tgt_north, tgt_east = gps_to_ned(
            home_lat, home_lon, goal.latitude, goal.longitude
        )

        # -------- MOVE --------
        while True:
            if self.cancel_requested:
                await self.drone.action.return_to_launch()
                return

            async for pos in self.drone.telemetry.position():
                curr_lat, curr_lon = pos.latitude_deg, pos.longitude_deg
                break

            dist = haversine(curr_lat, curr_lon, goal.latitude, goal.longitude)
            yaw = bearing_deg(curr_lat, curr_lon, goal.latitude, goal.longitude)

            if dist <= ARRIVAL_RADIUS_M:
                break

            await self.drone.offboard.set_position_ned(
                PositionNedYaw(tgt_north, tgt_east, -goal.altitude, yaw)
            )
            await asyncio.sleep(1 / SETPOINT_RATE_HZ)

        # -------- HOLD (SHORT) --------
        for _ in range(HOLD_TIME_SEC * SETPOINT_RATE_HZ):
            await self.drone.offboard.set_position_ned(
                PositionNedYaw(tgt_north, tgt_east, -goal.altitude, yaw)
            )
            await asyncio.sleep(1 / SETPOINT_RATE_HZ)

        await self.drone.action.return_to_launch()

    async def _start_offboard(self):
        for _ in range(10):
            await self.drone.offboard.set_position_ned(
                PositionNedYaw(0.0, 0.0, -CRUISE_ALT_M, 0.0)
            )
            await asyncio.sleep(0.1)

        await self.drone.offboard.start()


def main(args=None):
    rclpy.init(args=args)
    node = DeliveryOffboardManager()
    executor = MultiThreadedExecutor()
    try:
        rclpy.spin(node, executor)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
