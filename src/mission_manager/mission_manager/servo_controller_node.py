#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

import board
import busio
from adafruit_pca9685 import PCA9685

from servo_interfaces.srv import ControlServo


# ================== SERVO CONFIG ==================
SERVO_CONFIG = {
    1: {"channel": 0, "open": 95,  "close": 10},
    2: {"channel": 1, "open": 110, "close": 20},
    3: {"channel": 2, "open": 90,  "close": 0},
    4: {"channel": 3, "open": 120, "close": 15},
    5: {"channel": 4, "open": 100, "close": 5}
}

MIN_PULSE = 150
MAX_PULSE = 600


# ================== NODE ==================
class ServoController(Node):

    def __init__(self):
        super().__init__('servo_controller')

        # ----- I2C + PCA9685 -----
        i2c = busio.I2C(board.SCL, board.SDA)
        self.pca = PCA9685(i2c)
        self.pca.frequency = 50

        # ----- ROS 2 Service -----
        self.srv = self.create_service(
            ControlServo,
            'control_servo',
            self.handle_servo_request
        )

        self.get_logger().info("Servo Controller Service Ready")

    # ================== SERVO LOGIC ==================
    def set_angle(self, channel, angle):
        pulse = int(
            MIN_PULSE + (angle / 180.0) * (MAX_PULSE - MIN_PULSE)
        )
        self.pca.channels[channel].duty_cycle = pulse << 4

    # ================== SERVICE CALLBACK ==================
    def handle_servo_request(self, request, response):
        servo_id = request.servo_id

        if servo_id not in SERVO_CONFIG:
            response.success = False
            response.message = "Invalid servo ID"
            return response

        cfg = SERVO_CONFIG[servo_id]
        angle = cfg["open"] if request.open else cfg["close"]

        try:
            self.set_angle(cfg["channel"], angle)
            response.success = True
            response.message = (
                f"Servo {servo_id} "
                f"{'OPENED' if request.open else 'CLOSED'}"
            )
        except Exception as e:
            response.success = False
            response.message = str(e)

        return response


# ================== MAIN ==================
def main(args=None):
    rclpy.init(args=args)
    node = ServoController()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
