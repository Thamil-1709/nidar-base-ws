from launch import LaunchDescription
from launch.actions import ExecuteProcess
import os

# Constants
PX4_DIR = os.path.expanduser('~/PX4-Autopilot')
PX4_BIN = os.path.join(PX4_DIR, 'build/px4_sitl_default/bin/px4')

def generate_launch_description():

    # Common environment variables for both drones
    common_env = {
        'PX4_HOME_LAT': '13.093128',
        'PX4_HOME_LON': '79.973231',
        'PX4_HOME_ALT': '0',
        'PX4_HOME_YAW': '0',
        'PX4_SYS_AUTOSTART': '4001',
        'PX4_SIM_MODEL': 'gz_x500'
    }

    # Scout Drone (Instance 0)
    scout = ExecuteProcess(
        cmd=[
            PX4_BIN,
            '-i', '0', # Instance ID 0
            '-d'       # Use the default startup script
        ],
        cwd=PX4_DIR,
        additional_env={
            **common_env,
            'PX4_GZ_MODEL_POSE': '0,0,0,0,0,0'
        },
        output='screen'
    )

    # Spray Drone (Instance 1)
    # We offset the position to '3,0,0' to prevent spawning them on top of each other
    delivery = ExecuteProcess(
        cmd=[
            PX4_BIN,
            '-i', '1', # Instance ID 1
            '-d'
        ],
        cwd=PX4_DIR,
        additional_env={
            **common_env,
            'PX4_GZ_MODEL_POSE': '3,0,0,0,0,0'
        },
        output='screen'
    )

    return LaunchDescription([
        scout,
        delivery
    ])
