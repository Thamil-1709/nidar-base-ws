// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from mission_interfaces:srv/GetLawnmowerPath.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mission_interfaces/srv/get_lawnmower_path.hpp"


#ifndef MISSION_INTERFACES__SRV__DETAIL__GET_LAWNMOWER_PATH__BUILDER_HPP_
#define MISSION_INTERFACES__SRV__DETAIL__GET_LAWNMOWER_PATH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "mission_interfaces/srv/detail/get_lawnmower_path__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace mission_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetLawnmowerPath_Request_angle
{
public:
  explicit Init_GetLawnmowerPath_Request_angle(::mission_interfaces::srv::GetLawnmowerPath_Request & msg)
  : msg_(msg)
  {}
  ::mission_interfaces::srv::GetLawnmowerPath_Request angle(::mission_interfaces::srv::GetLawnmowerPath_Request::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mission_interfaces::srv::GetLawnmowerPath_Request msg_;
};

class Init_GetLawnmowerPath_Request_spacing
{
public:
  explicit Init_GetLawnmowerPath_Request_spacing(::mission_interfaces::srv::GetLawnmowerPath_Request & msg)
  : msg_(msg)
  {}
  Init_GetLawnmowerPath_Request_angle spacing(::mission_interfaces::srv::GetLawnmowerPath_Request::_spacing_type arg)
  {
    msg_.spacing = std::move(arg);
    return Init_GetLawnmowerPath_Request_angle(msg_);
  }

private:
  ::mission_interfaces::srv::GetLawnmowerPath_Request msg_;
};

class Init_GetLawnmowerPath_Request_safe_margin
{
public:
  explicit Init_GetLawnmowerPath_Request_safe_margin(::mission_interfaces::srv::GetLawnmowerPath_Request & msg)
  : msg_(msg)
  {}
  Init_GetLawnmowerPath_Request_spacing safe_margin(::mission_interfaces::srv::GetLawnmowerPath_Request::_safe_margin_type arg)
  {
    msg_.safe_margin = std::move(arg);
    return Init_GetLawnmowerPath_Request_spacing(msg_);
  }

private:
  ::mission_interfaces::srv::GetLawnmowerPath_Request msg_;
};

class Init_GetLawnmowerPath_Request_polygon_y
{
public:
  explicit Init_GetLawnmowerPath_Request_polygon_y(::mission_interfaces::srv::GetLawnmowerPath_Request & msg)
  : msg_(msg)
  {}
  Init_GetLawnmowerPath_Request_safe_margin polygon_y(::mission_interfaces::srv::GetLawnmowerPath_Request::_polygon_y_type arg)
  {
    msg_.polygon_y = std::move(arg);
    return Init_GetLawnmowerPath_Request_safe_margin(msg_);
  }

private:
  ::mission_interfaces::srv::GetLawnmowerPath_Request msg_;
};

class Init_GetLawnmowerPath_Request_polygon_x
{
public:
  Init_GetLawnmowerPath_Request_polygon_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetLawnmowerPath_Request_polygon_y polygon_x(::mission_interfaces::srv::GetLawnmowerPath_Request::_polygon_x_type arg)
  {
    msg_.polygon_x = std::move(arg);
    return Init_GetLawnmowerPath_Request_polygon_y(msg_);
  }

private:
  ::mission_interfaces::srv::GetLawnmowerPath_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::mission_interfaces::srv::GetLawnmowerPath_Request>()
{
  return mission_interfaces::srv::builder::Init_GetLawnmowerPath_Request_polygon_x();
}

}  // namespace mission_interfaces


namespace mission_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetLawnmowerPath_Response_waypoint_y
{
public:
  explicit Init_GetLawnmowerPath_Response_waypoint_y(::mission_interfaces::srv::GetLawnmowerPath_Response & msg)
  : msg_(msg)
  {}
  ::mission_interfaces::srv::GetLawnmowerPath_Response waypoint_y(::mission_interfaces::srv::GetLawnmowerPath_Response::_waypoint_y_type arg)
  {
    msg_.waypoint_y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mission_interfaces::srv::GetLawnmowerPath_Response msg_;
};

class Init_GetLawnmowerPath_Response_waypoint_x
{
public:
  Init_GetLawnmowerPath_Response_waypoint_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetLawnmowerPath_Response_waypoint_y waypoint_x(::mission_interfaces::srv::GetLawnmowerPath_Response::_waypoint_x_type arg)
  {
    msg_.waypoint_x = std::move(arg);
    return Init_GetLawnmowerPath_Response_waypoint_y(msg_);
  }

private:
  ::mission_interfaces::srv::GetLawnmowerPath_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::mission_interfaces::srv::GetLawnmowerPath_Response>()
{
  return mission_interfaces::srv::builder::Init_GetLawnmowerPath_Response_waypoint_x();
}

}  // namespace mission_interfaces


namespace mission_interfaces
{

namespace srv
{

namespace builder
{

class Init_GetLawnmowerPath_Event_response
{
public:
  explicit Init_GetLawnmowerPath_Event_response(::mission_interfaces::srv::GetLawnmowerPath_Event & msg)
  : msg_(msg)
  {}
  ::mission_interfaces::srv::GetLawnmowerPath_Event response(::mission_interfaces::srv::GetLawnmowerPath_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mission_interfaces::srv::GetLawnmowerPath_Event msg_;
};

class Init_GetLawnmowerPath_Event_request
{
public:
  explicit Init_GetLawnmowerPath_Event_request(::mission_interfaces::srv::GetLawnmowerPath_Event & msg)
  : msg_(msg)
  {}
  Init_GetLawnmowerPath_Event_response request(::mission_interfaces::srv::GetLawnmowerPath_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GetLawnmowerPath_Event_response(msg_);
  }

private:
  ::mission_interfaces::srv::GetLawnmowerPath_Event msg_;
};

class Init_GetLawnmowerPath_Event_info
{
public:
  Init_GetLawnmowerPath_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetLawnmowerPath_Event_request info(::mission_interfaces::srv::GetLawnmowerPath_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GetLawnmowerPath_Event_request(msg_);
  }

private:
  ::mission_interfaces::srv::GetLawnmowerPath_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::mission_interfaces::srv::GetLawnmowerPath_Event>()
{
  return mission_interfaces::srv::builder::Init_GetLawnmowerPath_Event_info();
}

}  // namespace mission_interfaces

#endif  // MISSION_INTERFACES__SRV__DETAIL__GET_LAWNMOWER_PATH__BUILDER_HPP_
