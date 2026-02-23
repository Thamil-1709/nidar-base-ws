import os
import random
import rclpy
from rclpy.node import Node

from shapely.geometry import Point, Polygon
from ament_index_python.packages import get_package_share_directory
from mission_interfaces.srv import TriggerRandomLocation

import xml.etree.ElementTree as ET


def load_polygon_from_kml(kml_path):
    tree = ET.parse(kml_path)
    root = tree.getroot()

    ns = {"kml": "http://www.opengis.net/kml/2.2"}
    coord_elements = root.findall(
        ".//kml:Polygon//kml:coordinates",
        ns
    )

    if not coord_elements:
        raise RuntimeError("No Polygon coordinates found in KML file")

    coords_text = coord_elements[0].text

    coords = []
    for coord in coords_text.replace("\n", " ").split():
        lon, lat, *_ = coord.split(",")
        coords.append((float(lon), float(lat)))

    if len(coords) < 3:
        raise RuntimeError("Invalid polygon in KML")

    return Polygon(coords)


class RandomLocationService(Node):

    def __init__(self):
        super().__init__("random_location_service")

        # 🔢 Service call counter
        self.call_count = 0

        pkg_share = get_package_share_directory("mission_manager")
        kml_file = os.path.join(pkg_share, "kml", "area.kml")

        self.polygon = load_polygon_from_kml(kml_file)

        self.create_service(
            TriggerRandomLocation,
            "trigger_random_location",
            self.trigger_callback
        )

        #self.get_logger().info("Random Location Service READY")
        self.get_logger().info(f"Polygon bounds: {self.polygon.bounds}")

    def random_point_inside(self):
        minx, miny, maxx, maxy = self.polygon.bounds

        while True:
            p = Point(
                random.uniform(minx, maxx),
                random.uniform(miny, maxy)
            )
            if self.polygon.contains(p):
                return p.y, p.x  # lat, lon

    def trigger_callback(self, request, response):
        # Increment service call count
        self.call_count += 1

        lat, lon = self.random_point_inside()

        response.latitude = lat
        response.longitude = lon
        response.call_count = self.call_count
        response.message = (
            f"victim detected #{self.call_count} | "
            f"Lat={lat:.6f}, Lon={lon:.6f} \n forwarding to delivery mission manager."
        )

        self.get_logger().info(response.message)
        return response


def main():
    rclpy.init()
    node = RandomLocationService()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
