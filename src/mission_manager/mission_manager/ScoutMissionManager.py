
import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer
from mission_interfaces.action import ScoutActionTrigger 
from geographic_msgs.msg import GeoPoint

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
        # initialize feedback message
        feedback_msg = ScoutActionTrigger.Feedback()
        complete = False
        current_location = GeoPoint()
        # task loop
        while not complete:
            self.get_logger().info('Scanning in progress...')
            current_location.latitude = 0.0  # Update with actual latitude
            current_location.altitude = 0.0  # Update with actual altitude
            current_location.longitude = 0.0  # Update with actual longitude
            self.get_logger().info(f'Current Location: {current_location}')
            feedback_msg.current_location = current_location
            complete = True


        goal_handle.publish_feedback(feedback_msg)
        self.get_logger().info('Feedback published.')
        if complete==True:
            result = ScoutActionTrigger.Result()
            result.success = True
            goal_handle.succeed()
            return result
        else:
            result = ScoutActionTrigger.Result()
            result.success = False
            goal_handle.abort()
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
