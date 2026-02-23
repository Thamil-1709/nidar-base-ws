from setuptools import find_packages, setup

package_name = 'mission_manager'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/kml', ['kml/area.kml']),
         ('share/' + package_name + '/launch' ,['launch/mission_launch.py'] ),
        
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='thamil',
    maintainer_email='tamilselvan1709@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
   # tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'lawnmower_planner = mission_manager.scout_path_generator:main',
            'data_config_services = mission_manager.DataConfigServices:main',
            'scout_path_generator = mission_manager.scout_path_generator:main',
            'delivery_mission_manager = mission_manager.DeliveryMissionManager:main',
            'scout_mission_manager = mission_manager.ScoutMissionManager:main',
            'telemetery_node = mission_manager.Telemetery:main',
            'model_service = mission_manager.random_location_service:main',
            'mission_manager = mission_manager.MissionManager:main',
             'multi_delivery_manager = mission_manager.MultiDeliveryManager:main',
             'MissionManagerSequence = mission_manager.MissionManagerSequence:main',
        ],
    },
)
