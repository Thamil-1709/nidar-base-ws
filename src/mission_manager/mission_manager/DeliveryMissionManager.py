#!/usr/bin/env python3

import rclpy
import asyncio
import threading

from rclpy.node import Node
from rclpy.action import ActionServer, GoalResponse, CancelResponse
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import ReentrantCallbackGroup

from mavsdk import System
from mavsdk.mission import MissionItem, MissionPlan

from mission_interfaces.action import DeliveryAction


class DeliveryMissionManager(Node):

    def __init__(self):
        super().__init__('delivery_mission_manager')
        self.get_logger().info("Delivery Mission Manager started")

        self.callback_group = ReentrantCallbackGroup()

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
            self._connect_and_prepare(),
            self.loop
        )

        # -------- ACTION SERVER --------
        self.action_server = ActionServer(
            self,
            DeliveryAction,
            'start_delivery',
            execute_callback=self.execute_callback,
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback,
            callback_group=self.callback_group
        )

    # =====================================================
    # ASYNC LOOP
    # =====================================================

    def _run_loop(self):
        asyncio.set_event_loop(self.loop)
        self.loop.run_forever()

    async def _connect_and_prepare(self):
        await self.drone.connect(system_address="udp://:14540")
        async for health in self.drone.telemetry.health():
            if health.is_armable and health.is_global_position_ok:
                self.get_logger().info("Drone ready")
                break

    # =====================================================
    # ACTION EXECUTION
    # =====================================================

    def execute_callback(self, goal_handle):
        self._active_goal = goal_handle
        self._cancel_requested = False

        result = DeliveryAction.Result()

        future = asyncio.run_coroutine_threadsafe(
            self._execute_async(goal_handle),
            self.loop
        )

        try:
            future.result()
            if self._cancel_requested:
                goal_handle.canceled()
                result.success = 0.0
            else:
                goal_handle.succeed()
                result.success = 1.0
        except Exception as e:
            self.get_logger().error(f"Delivery failed: {e}")
            goal_handle.abort()
            result.success = -1.0

        self._active_goal = None
        return result

    # =====================================================
    # DELIVERY LOGIC
    # =====================================================

    async def _execute_async(self, goal_handle):
        goal = goal_handle.request

        self.get_logger().info(
            f"Target: lat={goal.latitude}, lon={goal.longitude}, alt={goal.altitude}"
        )

        # ---- Mission waypoint ----
        mission_items = [
            MissionItem(
                goal.latitude,
                goal.longitude,
                goal.altitude,
                0.0,
                True,
                float("nan"),
                float("nan"),
                MissionItem.CameraAction.NONE,
                *[float("nan")] * 5,
                MissionItem.VehicleAction.NONE
            )
        ]

        await self.drone.mission.clear_mission()
        await self.drone.mission.upload_mission(
            MissionPlan(mission_items)
        )

        await self.drone.action.arm()
        await self.drone.mission.start_mission()

        await self._monitor_and_hold(goal_handle)

    async def _monitor_and_hold(self, goal_handle):
        arrived = False

        async for pos in self.drone.telemetry.position():

            if self._cancel_requested:
                await self.drone.mission.pause_mission()
                await self.drone.action.return_to_launch()
                return

            # ---- Feedback (FLOATS ONLY) ----
            feedback = DeliveryAction.Feedback()
            feedback.current_lat = pos.latitude_deg
            feedback.current_lon = pos.longitude_deg
            feedback.current_alt = pos.relative_altitude_m
            goal_handle.publish_feedback(feedback)

            # ---- Arrival ----
            if await self.drone.mission.is_mission_finished() and not arrived:
                arrived = True
                self.get_logger().info("Arrived at target, holding 60s")
                await asyncio.sleep(60)

                self.get_logger().info("Returning to launch")
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
    node = DeliveryMissionManager()
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
