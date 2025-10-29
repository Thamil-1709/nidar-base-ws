import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Float32, Int32
from geometry_msgs.msg import Point

#!/usr/bin/env python3


class TelemetryPublisher(Node):
    def __init__(self):
        super().__init__('telemetry_publisher')

        # publishers for Drone 1
        self.d1_type_pub = self.create_publisher(String, 'drone1/type', 10)
        self.d1_batt_pub = self.create_publisher(Float32, 'drone1/battery', 10)
        self.d1_alt_pub = self.create_publisher(Float32, 'drone1/altitude', 10)
        self.d1_speed_pub = self.create_publisher(Float32, 'drone1/speed', 10)
        self.d1_heading_pub = self.create_publisher(Int32, 'drone1/heading', 10)
        self.d1_loc_pub = self.create_publisher(Point, 'drone1/location', 10)
        self.d1_payload_pub = self.create_publisher(String, 'drone1/payload', 10)

        # publishers for Drone 2
        self.d2_type_pub = self.create_publisher(String, 'drone2/type', 10)
        self.d2_batt_pub = self.create_publisher(Float32, 'drone2/battery', 10)
        self.d2_alt_pub = self.create_publisher(Float32, 'drone2/altitude', 10)
        self.d2_speed_pub = self.create_publisher(Float32, 'drone2/speed', 10)
        self.d2_heading_pub = self.create_publisher(Int32, 'drone2/heading', 10)
        self.d2_loc_pub = self.create_publisher(Point, 'drone2/location', 10)
        self.d2_payload_pub = self.create_publisher(String, 'drone2/payload', 10)

        timer_period = 1.0  # seconds
        self.timer = self.create_timer(timer_period, self.publish_telemetry)

        # structured telemetry (not a single string)
        self.drone1 = {
            "type": "Scout Drone",
            "battery": 95.0,        # percent
            "altitude": 104.0,      # meters
            "speed": 15.0,          # km/h
            "heading": 158,         # degrees
            "location": (37.7751, -122.4199),
            "payload": ""
        }

        self.drone2 = {
            "type": "Delivery Drone",
            "battery": 77.0,
            "altitude": 94.0,
            "speed": 24.0,
            "heading": 167,
            "location": (37.7751, -122.4199),
            "payload": "Medical Kit"
        }

    def publish_telemetry(self):
        # Drone 1 messages
        tm = String()
        tm.data = self.drone1["type"]
        self.d1_type_pub.publish(tm)

        fb = Float32()
        fb.data = self.drone1["battery"]
        self.d1_batt_pub.publish(fb)

        fa = Float32()
        fa.data = self.drone1["altitude"]
        self.d1_alt_pub.publish(fa)

        fs = Float32()
        fs.data = self.drone1["speed"]
        self.d1_speed_pub.publish(fs)

        fh = Int32()
        fh.data = self.drone1["heading"]
        self.d1_heading_pub.publish(fh)

        p = Point()
        p.x, p.y = self.drone1["location"]
        p.z = 0.0
        self.d1_loc_pub.publish(p)

        fp = String()
        fp.data = self.drone1["payload"]
        self.d1_payload_pub.publish(fp)

        # Drone 2 messages
        tm2 = String()
        tm2.data = self.drone2["type"]
        self.d2_type_pub.publish(tm2)

        fb2 = Float32()
        fb2.data = self.drone2["battery"]
        self.d2_batt_pub.publish(fb2)

        fa2 = Float32()
        fa2.data = self.drone2["altitude"]
        self.d2_alt_pub.publish(fa2)

        fs2 = Float32()
        fs2.data = self.drone2["speed"]
        self.d2_speed_pub.publish(fs2)

        fh2 = Int32()
        fh2.data = self.drone2["heading"]
        self.d2_heading_pub.publish(fh2)

        p2 = Point()
        p2.x, p2.y = self.drone2["location"]
        p2.z = 0.0
        self.d2_loc_pub.publish(p2)

        fp2 = String()
        fp2.data = self.drone2["payload"]
        self.d2_payload_pub.publish(fp2)

        self.get_logger().info('Published structured telemetry for 2 drones')


def main(args=None):
    rclpy.init(args=args)
    node = TelemetryPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()