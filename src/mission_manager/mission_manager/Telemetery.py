import asyncio
import rclpy
from rclpy.node import Node

from geometry_msgs.msg import PoseStamped
from sensor_msgs.msg import BatteryState
from std_msgs.msg import Float32, String

from mavsdk import System


class ScoutMavsdkNode(Node):

    def __init__(self):
        super().__init__('scout_mavsdk_node')

        self.pose_pub = self.create_publisher(PoseStamped, '/scout/pose', 10)
        self.battery_pub = self.create_publisher(BatteryState, '/scout/battery', 10)
        self.speed_pub = self.create_publisher(Float32, '/scout/speed', 10)
        self.heading_pub = self.create_publisher(Float32, '/scout/heading', 10)
        self.conn_pub = self.create_publisher(String, '/scout/connection', 10)

        self.loop = asyncio.get_event_loop()
        self.loop.create_task(self.run())

        self.get_logger().info("🛰 Scout MAVSDK node started")

    async def run(self):
        drone = System()
        await drone.connect(system_address="udp://localhost:14445")

        async for state in drone.core.connection_state():
            if state.is_connected:
                self.conn_pub.publish(String(data="CONNECTED"))
                break

        async for pos in drone.telemetry.position():
            self.publish_position(pos)

    def publish_position(self, pos):
        msg = PoseStamped()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = "map"
        msg.pose.position.x = pos.longitude_deg
        msg.pose.position.y = pos.latitude_deg
        msg.pose.position.z = pos.relative_altitude_m
        self.pose_pub.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = ScoutMavsdkNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
