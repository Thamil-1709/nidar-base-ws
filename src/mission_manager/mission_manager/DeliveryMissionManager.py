import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer
from mission_interfaces.action import DeliveryActionTrigger


class DeliveryMissionManager(Node):
    def __init__(self):
        super().__init__('delivery_mission_manager')
        self.get_logger().info('Delivery Mission Manager is initialized.')
        self.queue = []
        self.current_mission = None
        self.action_server = ActionServer(
            self,
            DeliveryActionTrigger,
            'delivery_manager',
            self.handle_delivery_mission,
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback,
            
        )
        self.get_logger().info('Action server for delivery mission is ready.')

    def goal_callback(self, goal_request):
        self.get_logger().info('Received goal request for delivery mission.')
        return rclpy.action.GoalResponse.ACCEPT
    
    def cancel_callback(self, goal_handle):
        self.get_logger().info('Received cancel request for delivery mission.')
        return rclpy.action.CancelResponse.ACCEPT


    def handle_delivery_mission(self, goal_handle):
        self.get_logger().info('Handling delivery mission...')
        goal_handle.succeed()
        self.get_logger().info('Delivery mission completed successfully.')
    
    

def main(args=None):
    rclpy.init(args=args)
    delivery_mission_manager = DeliveryMissionManager()
    rclpy.spin(delivery_mission_manager)
    delivery_mission_manager.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()