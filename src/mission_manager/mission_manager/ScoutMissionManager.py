
import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer
from mission_interfaces.action import ScoutActionTrigger 


class ScoutMissionManager(Node):
    def __init__(self):
        super().__init__('scout_mission_manager')
        self.get_logger().info('Scout Mission Manager is initialized.')
        self.action_server = ActionServer(
            self,
            ScoutActionTrigger,
            "start_scan",
            self.scout_action_callback,
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback,
        )

    # Callback for handling the scout mission action
    def scout_action_callback(self, goal_handle):
        self.get_logger().info('Handling scout mission action...')
        goal = goal_handle.request
        self.get_logger().info(f'Received goal: {goal.waypoints}')
        self.get_logger().info('Scout mission action completed successfully.')
        
        
        result = ScoutActionTrigger.Result()
        result.success = True
        goal_handle.succeed()
        return result

    
    def goal_callback(self, goal_request):
        self.get_logger().info('Received goal request for scout mission.')
        return rclpy.action.GoalResponse.ACCEPT
    
    def cancel_callback(self, goal_handle):
        self.get_logger().info('Received cancel request for scout mission.')
        return rclpy.action.CancelResponse.ACCEPT
    


def main(args=None):
    rclpy.init(args=args)
    scout_mission_manager = ScoutMissionManager()
    rclpy.spin(scout_mission_manager)
    scout_mission_manager.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
