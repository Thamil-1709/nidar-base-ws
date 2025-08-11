cmake_minimum_required(VERSION 3.8)
project(mission_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/GetLawnmowerPath.srv"
  "srv/SetComConfig.srv"
  "srv/GetComConfig.srv"
  "srv/SetDroneConfig.srv"
  "srv/GetDroneConfig.srv"
  "srv/SetFlightTimeout.srv"
  "srv/GetFlightTimeout.srv"
  "action/DeliveryTriggerAction.action"
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
