# !../../../.venv/bin/python3
import rclpy
from rclpy.node import Node
from mission_interfaces.srv import GetLawnmowerPath
from pyproj import Transformer
import math

class LawnmowerPathServer(Node):
    def __init__(self):
        super().__init__('lawnmower_path_server')
        self.srv = self.create_service(
            GetLawnmowerPath, 'get_scout_path', self.lawnmower_callback)
        self.get_logger().info('Lawnmower path service is ready.')

        # EPSG:4326 (lat/lon) -> EPSG:32644 (UTM Zone 44N)
        self.transformer = Transformer.from_crs("EPSG:4326", "EPSG:32644", always_xy=True)
        self.reverse_transformer = Transformer.from_crs("EPSG:32644","EPSG:4326",always_xy=(True))

    def lawnmower_callback(self, request, response):
        # Convert lat/lon to UTM x/y
        lat_lon_coords = list(zip(request.polygon_x, request.polygon_y))  # Note: polygon_x = lon, polygon_y = lat
        transformed_coords = [self.transformer.transform(lon, lat) for lon, lat in lat_lon_coords]
        polygon_x = [round(x, 1) for x, _ in transformed_coords]
        polygon_y = [round(y, 1) for _, y in transformed_coords]

        safe_margin = request.safe_margin
        spacing = request.spacing
        angle_deg = request.angle

        self.get_logger().info(
            f'Received {len(polygon_x)} points. Margin: {safe_margin}, Spacing: {spacing}, Angle: {angle_deg} deg'
        )

        # Convert angle to radians
        angle_rad = math.radians(angle_deg)

        # --- Rotate polygon ---
        cos_theta = math.cos(-angle_rad)
        sin_theta = math.sin(-angle_rad)

        rotated_polygon = []
        for x, y in zip(polygon_x, polygon_y):
            x_rot = cos_theta * x - sin_theta * y
            y_rot = sin_theta * x + cos_theta * y
            rotated_polygon.append((x_rot, y_rot))

        x_coords = [p[0] for p in rotated_polygon]
        y_coords = [p[1] for p in rotated_polygon]

        min_y = min(y_coords) + safe_margin
        max_y = max(y_coords) - safe_margin
        min_x = min(x_coords) + safe_margin
        max_x = max(x_coords) - safe_margin

        # --- Generate lawnmower path ---
        waypoints_rotated = []
        y = min_y
        direction = 1
        
        

        while y <= max_y:
            if direction == 1:
                waypoints_rotated.append((min_x, y))
                waypoints_rotated.append((max_x, y))
            else:
                waypoints_rotated.append((max_x, y))
                waypoints_rotated.append((min_x, y))
            y += spacing
            direction *= -1
        waypoints_rotated = [self.reverse_transformer.transform(lon, lat) for lon, lat in waypoints_rotated]
        # --- Add start and end points ---
        
        # --- Rotate waypoints back to original frame ---
        cos_theta = math.cos(angle_rad)
        sin_theta = math.sin(angle_rad)
        for x_r, y_r in waypoints_rotated:
            x_orig = cos_theta * x_r - sin_theta * y_r
            y_orig = sin_theta * x_r + cos_theta * y_r

            response.waypoint_x.append(x_orig)
            response.waypoint_y.append(y_orig)
        self.get_logger().info(f"Generated {len(response.waypoint_x)} waypoints.")
        
        return response


def main(args=None):
    rclpy.init(args=args)
    node = LawnmowerPathServer()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
