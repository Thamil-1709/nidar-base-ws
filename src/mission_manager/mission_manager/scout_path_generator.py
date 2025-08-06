import rclpy
from rclpy.node import Node
import math

from mission_interfaces.srv import GetLawnmowerPath

class LawnMowerPathGenerator(Node):

    def __init__(self):
        super().__init__('lawnmower_path_server')
        self.srv = self.create_service(
            GetLawnmowerPath,
            '/get_lawnmower_path',
            self.generate_path_callback
        )
        self.get_logger().info('Lawnmower Path Service is ready...')

    def generate_path_callback(self, request, response):
        x_coords = list(request.polygon_x)
        y_coords = list(request.polygon_y)
        spacing = request.spacing
        safe_margin = request.safe_margin
        angle = math.radians(request.angle)

        if len(x_coords) < 3 or len(x_coords) != len(y_coords):
            self.get_logger().error('Invalid polygon input.')
            return response

        # Step 1: Rotate polygon to simplify path generation
        rotated_coords = [self.rotate(x, y, angle) for x, y in zip(x_coords, y_coords)]
        min_x = min([p[0] for p in rotated_coords])
        max_x = max([p[0] for p in rotated_coords])

        # Step 2: Generate lines in rotated space
        lines = []
        x = min_x + safe_margin
        while x <= max_x - safe_margin:
            lines.append(x)
            x += spacing

        # Step 3: Get intersection points for each line
        waypoints = []
        for i, x_line in enumerate(lines):
            intersections = []
            for j in range(len(rotated_coords)):
                x1, y1 = rotated_coords[j]
                x2, y2 = rotated_coords[(j + 1) % len(rotated_coords)]
                if (x1 - x_line) * (x2 - x_line) < 0:
                    t = (x_line - x1) / (x2 - x1)
                    y_intersect = y1 + t * (y2 - y1)
                    intersections.append((x_line, y_intersect))
            intersections.sort(key=lambda p: p[1])
            for k in range(0, len(intersections), 2):
                if k + 1 < len(intersections):
                    p1 = intersections[k]
                    p2 = intersections[k + 1]
                    segment = [p1, p2] if i % 2 == 0 else [p2, p1]
                    waypoints.extend(segment)

        # Step 4: Rotate waypoints back
        rotated_back = [self.rotate(x, y, -angle) for x, y in waypoints]
        response.waypoint_x = [float(x) for x, y in rotated_back]
        response.waypoint_y = [float(y) for x, y in rotated_back]
        return response

    def rotate(self, x, y, angle):
        cos_a = math.cos(angle)
        sin_a = math.sin(angle)
        x_rot = x * cos_a - y * sin_a
        y_rot = x * sin_a + y * cos_a
        return (x_rot, y_rot)


def main(args=None):
    rclpy.init(args=args)
    node = LawnMowerPathGenerator()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    rclpy.shutdown()


if __name__ == '__main__':
    main()
