import rclpy
from rclpy.node import Node
from custom_msgs.msg import VictimDetection
from sensor_msgs.msg import CameraInfo, NavSatFix
from geometry_msgs.msg import PoseStamped
import numpy as np
import sys
import os
import yaml
from ament_index_python.packages import get_package_share_directory
from pyproj import Proj, transform
from scipy.spatial.transform import Rotation as R

from yolo_node.utils.img_coords import pixel_to_cam_vector

def enu_to_ecef(lat, lon, alt, enu_point):
    """
    Converts an ENU point to ECEF coordinates.
    """
    a = 6378137.0  # WGS84 semi-major axis
    e_sq = 6.69437999014e-3  # WGS84 first eccentricity squared

    lat_rad = np.radians(lat)
    lon_rad = np.radians(lon)

    N = a / np.sqrt(1 - e_sq * np.sin(lat_rad)**2)

    x0 = (N + alt) * np.cos(lat_rad) * np.cos(lon_rad)
    y0 = (N + alt) * np.cos(lat_rad) * np.sin(lon_rad)
    z0 = ((1 - e_sq) * N + alt) * np.sin(lat_rad)

    R = np.array([
        [-np.sin(lon_rad), -np.sin(lat_rad) * np.cos(lon_rad), np.cos(lat_rad) * np.cos(lon_rad)],
        [np.cos(lon_rad), -np.sin(lat_rad) * np.sin(lon_rad), np.cos(lat_rad) * np.sin(lon_rad)],
        [0, np.cos(lat_rad), np.sin(lat_rad)]
    ])

    ecef_offset = R @ enu_point
    return np.array([x0, y0, z0]) + ecef_offset

class Img2GpsNode(Node):
    def __init__(self):
        super().__init__('img2gps_node')
        self.detection_subscription = self.create_subscription(
            VictimDetection,
            '/victim_detection_data',
            self.detection_callback,
            10
        )
        self.camera_info_subscription = self.create_subscription(
            CameraInfo,
            '/camera/camera_info',
            self.camera_info_callback,
            10
        )
        self.pose_subscription = self.create_subscription(
            PoseStamped,
            '/mav/pose',
            self.pose_callback,
            10
        )
        self.gps_subscription = self.create_subscription(
            NavSatFix,
            '/mav/gps',
            self.gps_callback,
            10
        )
        self.gps_publisher = self.create_publisher(NavSatFix, '/victim_gps_data', 10)

        self.camera_matrix = None
        self.dist_coeffs = None
        self.drone_pose = None
        self.drone_gps = None
        self.R_cam_to_body = None

        # Load camera extrinsics
        extrinsics_path = os.path.join(
            get_package_share_directory('human_detect_pkg'),
            'config', 'camera_extrinsics.yaml'
        )
        with open(extrinsics_path, 'r') as f:
            extrinsics = yaml.safe_load(f)
            rpy_deg = extrinsics['rpy_deg']
            self.R_cam_to_body = R.from_euler('xyz', rpy_deg, degrees=True).as_matrix()
            self.get_logger().info(f"Loaded camera extrinsics: {rpy_deg}")

    def camera_info_callback(self, msg):
        self.camera_matrix = np.array(msg.k).reshape((3, 3))
        self.dist_coeffs = np.array(msg.d)

    def pose_callback(self, msg):
        self.drone_pose = msg.pose

    def gps_callback(self, msg):
        self.drone_gps = msg

    def detection_callback(self, msg):
        if self.camera_matrix is None or self.drone_pose is None or self.drone_gps is None:
            return

        # Get the center of the bounding box
        u = msg.bounding_box.x_offset + msg.bounding_box.width / 2
        v = msg.bounding_box.y_offset + msg.bounding_box.height / 2

        # Get the bearing vector in the camera frame
        bearing_vector_cam = pixel_to_cam_vector(u, v, self.camera_matrix, self.dist_coeffs)

        bearing_vector_body = self.R_cam_to_body @ bearing_vector_cam

        # Get the drone's orientation
        drone_orientation = self.drone_pose.orientation
        R_body_to_world = R.from_quat([drone_orientation.x, drone_orientation.y, drone_orientation.z, drone_orientation.w]).as_matrix()

        # Get the bearing vector in the world frame
        bearing_vector_world = R_body_to_world @ bearing_vector_body

        # Intersect the bearing vector with the ground plane
        ground_alt = 0.0  # Assume ground is at 0m altitude
        t = (ground_alt - self.drone_pose.position.z) / bearing_vector_world[2]

        if t < 0:
            self.get_logger().warn("Intersection with ground plane is behind the camera.")
            return

        intersection_point_enu = np.array([self.drone_pose.position.x, self.drone_pose.position.y, self.drone_pose.position.z]) + t * bearing_vector_world

        # Convert the intersection point to lat/lon
        intersection_point_ecef = enu_to_ecef(
            self.drone_gps.latitude,
            self.drone_gps.longitude,
            self.drone_gps.altitude,
            intersection_point_enu
        )
        ecef = Proj(proj='geocent', ellps='WGS84', datum='WGS84')
        lla = Proj(proj='latlong', ellps='WGS84', datum='WGS84')
        lon, lat, alt = transform(ecef, lla, intersection_point_ecef[0], intersection_point_ecef[1], intersection_point_ecef[2], radians=False)


        # Estimate uncertainty based on bounding box size
        # A larger bounding box means the object is closer, so less uncertainty
        uncertainty = 1.0 / (msg.bounding_box.width * msg.bounding_box.height)

        # Publish the GPS coordinates
        gps_msg = NavSatFix()
        gps_msg.header.stamp = self.get_clock().now().to_msg()
        gps_msg.header.frame_id = 'map'
        gps_msg.latitude = lat
        gps_msg.longitude = lon
        gps_msg.altitude = alt
        # Add uncertainty to the message
        gps_msg.position_covariance[0] = uncertainty
        gps_msg.position_covariance[4] = uncertainty
        gps_msg.position_covariance[8] = uncertainty
        gps_msg.position_covariance_type = NavSatFix.COVARIANCE_TYPE_DIAGONAL_KNOWN

        self.gps_publisher.publish(gps_msg)

        self.get_logger().info(f"Published victim GPS: {lat}, {lon} with uncertainty {uncertainty}")

def main(args=None):
    rclpy.init(args=args)
    node = Img2GpsNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
