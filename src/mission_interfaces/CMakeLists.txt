cmake_minimum_required(VERSION 3.8)
project(mission_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(geographic_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/GetLawnmowerPath.srv"
  "srv/SetComConfig.srv"
  "srv/GetComConfig.srv"
  "srv/SetDroneConfig.srv"
  "srv/GetDroneConfig.srv"
  "srv/SetFlightTimeout.srv"
  "srv/GetFlightTimeout.srv"
  "srv/ControlServo.srv"
  "srv/TriggerRandomLocation.srv"
  "srv/GetMissionBoundary.srv"
  "srv/SetMissionBoundary.srv"
  "action/DeliveryActionTrigger.action"
  "action/ScoutActionTrigger.action"
  "msg/Empty.msg"
 
  "srv/StartMission.srv"
  DEPENDENCIES geographic_msgs
)

# 🔥 THIS LINE IS MISSING IN YOUR VERSION
ament_export_dependencies(rosidl_default_runtime)

ament_package()
