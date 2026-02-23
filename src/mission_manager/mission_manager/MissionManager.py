#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from rclpy.executors import MultiThreadedExecutor

from geographic_msgs.msg import GeoPoint

from mission_interfaces.srv import StartMission
from mission_interfaces.action import ScoutActionTrigger
from mission_interfaces.action import DeliveryActionTrigger


class MissionManager(Node):

    def __init__(self):
        super().__init__('mission_manager')

        self.get_logger().info("Mission Manager Started")

        self.victim_queue = []
        self.delivery_busy = False
        self.scout_running = False

        # Service
        self.start_service = self.create_service(
            StartMission,
            'start_mission',
            self.start_mission_callback
        )

        # Victim subscription
        self.create_subscription(
            GeoPoint,
            '/scout/victim_detected',
            self.victim_callback,
            10
        )

        # Action clients
        self.scout_client = ActionClient(
            self,
            ScoutActionTrigger,
            'start_scan'
        )

        self.delivery_client = ActionClient(
            self,
            DeliveryActionTrigger,
            'start_delivery'
        )

        self.create_timer(1.0, self.process_queue)

    # ======================================================
    # SERVICE: Web → Orchestrator
    # ======================================================

    def start_mission_callback(self, request, response):

        if self.scout_running:
            response.accepted = False
            return response

        if not request.waypoints:
            self.get_logger().warn("No waypoints received")
            response.accepted = False
            return response

        self.get_logger().info("Starting Scout with received waypoints")

        self.scout_client.wait_for_server()

        goal_msg = ScoutActionTrigger.Goal()
        goal_msg.waypoints = request.waypoints

        self.scout_client.send_goal_async(goal_msg)

        self.scout_running = True
        response.accepted = True

        return response

    # ======================================================
    # Victim Detection
    # ======================================================

    def victim_callback(self, msg: GeoPoint):
        self.get_logger().info(
            f"Victim detected at {msg.latitude}, {msg.longitude}"
        )
        self.victim_queue.append(msg)

    # ======================================================
    # Delivery Queue Processor
    # ======================================================

    def process_queue(self):

        if self.delivery_busy:
            return

        if not self.victim_queue:
            return

        victim = self.victim_queue.pop(0)

        self.get_logger().info("Dispatching Delivery Drone")

        self.delivery_client.wait_for_server()

        goal_msg = DeliveryActionTrigger.Goal()
        goal_msg.target_location = victim

        send_goal_future = self.delivery_client.send_goal_async(goal_msg)
        send_goal_future.add_done_callback(self.delivery_response_callback)

        self.delivery_busy = True

    # ======================================================
    # Delivery Callbacks
    # ======================================================

    def delivery_response_callback(self, future):

        goal_handle = future.result()

        if not goal_handle.accepted:
            self.get_logger().info("Delivery goal rejected")
            self.delivery_busy = False
            return

        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self.delivery_result_callback)

    def delivery_result_callback(self, future):
        self.get_logger().info("Delivery completed")
        self.delivery_busy = False


def main(args=None):
    rclpy.init(args=args)

    node = MissionManager()
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
