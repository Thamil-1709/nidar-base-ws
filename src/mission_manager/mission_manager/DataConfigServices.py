#! ../../../.venv/bin/python3
import rclpy
from rclpy.node import Node
from rosidl_runtime_py import message_to_ordereddict
from tinydb import TinyDB, Query
from mission_interfaces.srv import GetComConfig, SetComConfig, GetDroneConfig, SetDroneConfig,SetFlightTimeout, GetFlightTimeout
import os

class StoreConfig(Node):
    def __init__(self):
        super().__init__('storage_node')
        self.config_file = 'config.json'  
        if os.path.exists(self.config_file):
            self.get_logger().info(f'Using existing config file: {self.config_file}')
        else:
            self.get_logger().info(f'Config file not found, creating new one at: {self.config_file}')
            open(self.config_file, 'w').close()
        self.db = TinyDB(self.config_file)
        self.get_logger().info(f'Storage node initialized with database at {self.config_file}')
        self.create_service(
            SetComConfig, 'set_com_data', self.set_coms_config_callback
        )
        self.create_service(
            GetComConfig, 'get_com_data', self.get_coms_config_callback
        )
        self.create_service(
            GetDroneConfig, 'get_drone_config', self.get_drone_config_callback
        )
        self.create_service(
            SetDroneConfig, 'set_drone_config', self.set_drone_config_callback
        )
        self.create_service(
            GetFlightTimeout, 'get_flight_timeout', self.get_flight_timeout_callback
        )
        self.create_service(
            SetFlightTimeout, 'set_flight_timeout', self.set_flight_timeout_callback
        )
        
        self.get_logger().info('Service for storing and retrieving mission data is ready.')
            
    def store_config(self, key, value):
        Config = Query()
        print(self.db.contains(Config[f"{key}"] == key))
        if self.db.contains(Config.key == key):
            self.db.update({key: value}, Config.key == key)
            self.get_logger().info(f'Updated {key} with value {value} in {self.config_file}')
        else:
            value = {key: value, 'key': key}
            self.db.insert(value)
        self.get_logger().info(f'Stored {key} with value {value} in {self.config_file}')

        return True

    def retrieve_config(self, key):
        Config = Query()
        result = self.db.search(Config.key == key)
        if result:
            value = result[0][key]
            self.get_logger().info(f'Retrieved {key} with value {value} from {self.config_file}')
            return value
        else:
            self.get_logger().warning(f'Key {key} not found in {self.config_file}')
            return None
        
    def delete_config(self, key):
        Config = Query()
        self.db.remove(Config.key == key)
        self.get_logger().info(f'Deleted {key} from {self.config_file}')
        return True

    def set_coms_config_callback(self, request, response):
        self.get_logger().info(f'Received request for key: {request}')
        # if request not in ['scout_video_port', 'scout_video_ip', 'delivery_video_port', 'delivery_video_ip', 'delivery_video_topic', 'scout_video_topic']:
        #     response.success = False
        #     response.message = f'Invalid request'
        #     return response
        print(message_to_ordereddict(request))
        temp = dict(message_to_ordereddict(request))
        # Remove empty strings from the dictionary
        temp = {k: v for k, v in temp.items() if v != ''}

        print(temp)

        self.store_config("communication_config", temp)
        response.success = True
        response.message = f'Successfully stored communication configuration'
        return response

    def get_coms_config_callback(self, request, response):
        self.get_logger().info(f'Retrieving config for key: {request}')
        value = self.retrieve_config("communication_config")
        if value is not None:
            self.get_logger().info(f'Config retrieved: {value}')
            response.scout_video_port = value.get('scout_video_port', '')
            response.scout_video_ip = value.get('scout_video_ip', '')
            response.delivery_video_port = value.get('delivery_video_port', '')
            response.delivery_video_ip = value.get('delivery_video_ip', '')
            response.ros_ip = value.get('ros_ip', '')
            response.ros_port = value.get('ros_port', '')
            response.success = True
            response.message = f'Successfully retrieved config for {request}'
        else:
            response.scout_video_port = ''
            response.scout_video_ip = ''
            response.delivery_video_port = ''
            response.delivery_video_ip = ''
            response.ros_ip = ''
            response.ros_port = ''
            response.success = False
            response.message = f'Failed to retrieve config for {request}'
            self.get_logger().warning(response.message)
        return response
    

    def get_drone_config_callback(self, request, response):
        self.get_logger().info('Retrieving drone configuration')
        value = self.retrieve_config("drone_config")
        if value is not None:
            response.delivery_topic = value.get('delivery_topic', '')
            response.scout_topic = value.get('scout_topic', '')
            response.success = True
            response.message = 'Successfully retrieved drone configuration'
        else:
            response.delivery_topic = ''
            response.scout_topic = ''
            response.success = False
            response.message = 'Failed to retrieve drone configuration'
            self.get_logger().warning(response.message)
        return response
    
    def set_drone_config_callback(self, request, response):
        self.get_logger().info('Setting drone configuration')
        if request.delivery_topic and request.scout_topic:
            temp = dict(message_to_ordereddict(request))
            # Remove empty strings from the dictionary
            temp = {k: v for k, v in temp.items() if v != ''}
            self.get_logger().info(f'Storing drone config: {temp}')
            self.store_config("drone_config", temp)
            response.success = True
            response.message = 'Successfully set drone configuration'
        else:
            response.success = False
            response.message = 'Invalid drone configuration data'
            self.get_logger().warning(response.message)
        return response
    
    def get_flight_timeout_callback(self, request, response):
        self.get_logger().info('Retrieving flight timeout configuration')
        value = self.retrieve_config("flight_timeout")
        if value is not None:
            response.timeout = value.get('timeout', 0)
            response.success = True
            response.message = 'Successfully retrieved flight timeout configuration'
        else:
            response.timeout = 0
            response.success = False
            response.message = 'Failed to retrieve flight timeout configuration'
            self.get_logger().warning(response.message)

        return response
    
    def set_flight_timeout_callback(self, request, response):
        self.get_logger().info('Setting flight timeout configuration')
        if request.timeout >= 0:
            temp = {
                'timeout': request.timeout
            }
            self.store_config("flight_timeout", temp)
            response.success = True
            response.message = 'Successfully set flight timeout configuration'
        else:
            response.success = False
            response.message = 'Invalid flight timeout value'
            self.get_logger().warning(response.message)
        return response


def main(args=None):
    rclpy.init(args=args)
    node = StoreConfig()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()