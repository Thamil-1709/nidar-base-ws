import rclpy
from rclpy.node import Node
from custom_msgs.msg import GeotaggedImage, VictimDetection
from sensor_msgs.msg import Image, RegionOfInterest
from cv_bridge import CvBridge
from ultralytics import YOLO
import cv2
import uuid
import os
from ament_index_python.packages import get_package_share_directory

class ModelInferenceNode(Node):
    def __init__(self):
        super().__init__('model_inference_node')
        self.subscription = self.create_subscription(
            GeotaggedImage,
            '/scout/geotagged_image_data',
            self.callback,
            10
        )
        self.get_logger().info("Model Inference Node has been started.")
        self.publisher = self.create_publisher(VictimDetection, '/victim_detection_data', 10)
        model_path = os.path.join(
            get_package_share_directory('model_inference'),
            'models', 'best.pt'
        )
        self.model = YOLO(model_path)
        self.bridge = CvBridge()

    def callback(self, msg):
        frame = self.bridge.imgmsg_to_cv2(msg.image, desired_encoding='bgr8')
        results = self.model(frame)
        boxes = results[0].boxes

        for box in boxes:
            if int(box.cls[0]) == 0:  # class 'person'
                conf = float(box.conf[0])
                if conf < 0.5:
                    continue

                x1, y1, x2, y2 = map(int, box.xyxy[0])
                cropped = frame[y1:y2, x1:x2]

                det_msg = VictimDetection()
                det_msg.cropped_image = self.bridge.cv2_to_imgmsg(cropped, "bgr8")
                det_msg.latitude = msg.latitude
                det_msg.longitude = msg.longitude
                det_msg.confidence = conf
                det_msg.detection_id = str(uuid.uuid4())
                det_msg.bounding_box = RegionOfInterest()
                det_msg.bounding_box.x_offset = x1
                det_msg.bounding_box.y_offset = y1
                det_msg.bounding_box.width = x2 - x1
                det_msg.bounding_box.height = y2 - y1


                self.publisher.publish(det_msg)
                self.get_logger().info(f"Human detected: {conf:.2f}")

def main(args=None):
    rclpy.init(args=args)
    node = ModelInferenceNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
