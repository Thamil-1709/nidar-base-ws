#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    lawnmower_planner = Node(
        package='mission_manager',
        executable='lawnmower_planner',
        name='lawnmower_planner',
        output='screen'
    )

    mission_manager = Node(
        package='mission_manager',
        executable='mission_manager',
        name='mission_manager',
        output='screen'
    )

    data_config_services = Node(
        package='mission_manager',
        executable='data_config_services',
        name='data_config_services',
        output='screen'
    )

    scout_path_generator = Node(
        package='mission_manager',
        executable='scout_path_generator',
        name='scout_path_generator',
        output='screen'
    )

    delivery_mission_manager = Node(
        package='mission_manager',
        executable='delivery_mission_manager',
        name='delivery_mission_manager',
        output='screen'
    )

    scout_mission_manager = Node(
        package='mission_manager',
        executable='scout_mission_manager',
        name='scout_mission_manager',
        output='screen'
    )

    telemetery_node = Node(
        package='mission_manager',
        executable='telemetery_node',
        name='telemetery_node',
        output='screen'
    )

    model_service = Node(
        package='mission_manager',
        executable='model_service',
        name='model_service',
        output='screen'
    )

    return LaunchDescription([
        lawnmower_planner,
        data_config_services,
        scout_path_generator,
        mission_manager,
        #delivery_mission_manager,
        scout_mission_manager,
        #telemetery_node,
        #model_service,
    ])
