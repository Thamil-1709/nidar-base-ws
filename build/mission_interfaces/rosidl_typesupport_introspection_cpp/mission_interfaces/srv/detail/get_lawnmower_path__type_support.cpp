// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from mission_interfaces:srv/GetLawnmowerPath.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "mission_interfaces/srv/detail/get_lawnmower_path__functions.h"
#include "mission_interfaces/srv/detail/get_lawnmower_path__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace mission_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetLawnmowerPath_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) mission_interfaces::srv::GetLawnmowerPath_Request(_init);
}

void GetLawnmowerPath_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<mission_interfaces::srv::GetLawnmowerPath_Request *>(message_memory);
  typed_message->~GetLawnmowerPath_Request();
}

size_t size_function__GetLawnmowerPath_Request__polygon_x(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetLawnmowerPath_Request__polygon_x(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__GetLawnmowerPath_Request__polygon_x(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetLawnmowerPath_Request__polygon_x(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__GetLawnmowerPath_Request__polygon_x(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__GetLawnmowerPath_Request__polygon_x(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__GetLawnmowerPath_Request__polygon_x(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__GetLawnmowerPath_Request__polygon_x(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetLawnmowerPath_Request__polygon_y(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetLawnmowerPath_Request__polygon_y(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__GetLawnmowerPath_Request__polygon_y(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetLawnmowerPath_Request__polygon_y(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__GetLawnmowerPath_Request__polygon_y(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__GetLawnmowerPath_Request__polygon_y(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__GetLawnmowerPath_Request__polygon_y(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__GetLawnmowerPath_Request__polygon_y(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetLawnmowerPath_Request_message_member_array[5] = {
  {
    "polygon_x",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces::srv::GetLawnmowerPath_Request, polygon_x),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetLawnmowerPath_Request__polygon_x,  // size() function pointer
    get_const_function__GetLawnmowerPath_Request__polygon_x,  // get_const(index) function pointer
    get_function__GetLawnmowerPath_Request__polygon_x,  // get(index) function pointer
    fetch_function__GetLawnmowerPath_Request__polygon_x,  // fetch(index, &value) function pointer
    assign_function__GetLawnmowerPath_Request__polygon_x,  // assign(index, value) function pointer
    resize_function__GetLawnmowerPath_Request__polygon_x  // resize(index) function pointer
  },
  {
    "polygon_y",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces::srv::GetLawnmowerPath_Request, polygon_y),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetLawnmowerPath_Request__polygon_y,  // size() function pointer
    get_const_function__GetLawnmowerPath_Request__polygon_y,  // get_const(index) function pointer
    get_function__GetLawnmowerPath_Request__polygon_y,  // get(index) function pointer
    fetch_function__GetLawnmowerPath_Request__polygon_y,  // fetch(index, &value) function pointer
    assign_function__GetLawnmowerPath_Request__polygon_y,  // assign(index, value) function pointer
    resize_function__GetLawnmowerPath_Request__polygon_y  // resize(index) function pointer
  },
  {
    "safe_margin",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces::srv::GetLawnmowerPath_Request, safe_margin),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "spacing",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces::srv::GetLawnmowerPath_Request, spacing),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "angle",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces::srv::GetLawnmowerPath_Request, angle),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetLawnmowerPath_Request_message_members = {
  "mission_interfaces::srv",  // message namespace
  "GetLawnmowerPath_Request",  // message name
  5,  // number of fields
  sizeof(mission_interfaces::srv::GetLawnmowerPath_Request),
  false,  // has_any_key_member_
  GetLawnmowerPath_Request_message_member_array,  // message members
  GetLawnmowerPath_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  GetLawnmowerPath_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetLawnmowerPath_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetLawnmowerPath_Request_message_members,
  get_message_typesupport_handle_function,
  &mission_interfaces__srv__GetLawnmowerPath_Request__get_type_hash,
  &mission_interfaces__srv__GetLawnmowerPath_Request__get_type_description,
  &mission_interfaces__srv__GetLawnmowerPath_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace mission_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<mission_interfaces::srv::GetLawnmowerPath_Request>()
{
  return &::mission_interfaces::srv::rosidl_typesupport_introspection_cpp::GetLawnmowerPath_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, mission_interfaces, srv, GetLawnmowerPath_Request)() {
  return &::mission_interfaces::srv::rosidl_typesupport_introspection_cpp::GetLawnmowerPath_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__functions.h"
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace mission_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetLawnmowerPath_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) mission_interfaces::srv::GetLawnmowerPath_Response(_init);
}

void GetLawnmowerPath_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<mission_interfaces::srv::GetLawnmowerPath_Response *>(message_memory);
  typed_message->~GetLawnmowerPath_Response();
}

size_t size_function__GetLawnmowerPath_Response__waypoint_x(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetLawnmowerPath_Response__waypoint_x(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__GetLawnmowerPath_Response__waypoint_x(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetLawnmowerPath_Response__waypoint_x(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__GetLawnmowerPath_Response__waypoint_x(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__GetLawnmowerPath_Response__waypoint_x(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__GetLawnmowerPath_Response__waypoint_x(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__GetLawnmowerPath_Response__waypoint_x(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetLawnmowerPath_Response__waypoint_y(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetLawnmowerPath_Response__waypoint_y(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__GetLawnmowerPath_Response__waypoint_y(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetLawnmowerPath_Response__waypoint_y(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__GetLawnmowerPath_Response__waypoint_y(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__GetLawnmowerPath_Response__waypoint_y(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__GetLawnmowerPath_Response__waypoint_y(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__GetLawnmowerPath_Response__waypoint_y(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetLawnmowerPath_Response_message_member_array[2] = {
  {
    "waypoint_x",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces::srv::GetLawnmowerPath_Response, waypoint_x),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetLawnmowerPath_Response__waypoint_x,  // size() function pointer
    get_const_function__GetLawnmowerPath_Response__waypoint_x,  // get_const(index) function pointer
    get_function__GetLawnmowerPath_Response__waypoint_x,  // get(index) function pointer
    fetch_function__GetLawnmowerPath_Response__waypoint_x,  // fetch(index, &value) function pointer
    assign_function__GetLawnmowerPath_Response__waypoint_x,  // assign(index, value) function pointer
    resize_function__GetLawnmowerPath_Response__waypoint_x  // resize(index) function pointer
  },
  {
    "waypoint_y",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces::srv::GetLawnmowerPath_Response, waypoint_y),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetLawnmowerPath_Response__waypoint_y,  // size() function pointer
    get_const_function__GetLawnmowerPath_Response__waypoint_y,  // get_const(index) function pointer
    get_function__GetLawnmowerPath_Response__waypoint_y,  // get(index) function pointer
    fetch_function__GetLawnmowerPath_Response__waypoint_y,  // fetch(index, &value) function pointer
    assign_function__GetLawnmowerPath_Response__waypoint_y,  // assign(index, value) function pointer
    resize_function__GetLawnmowerPath_Response__waypoint_y  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetLawnmowerPath_Response_message_members = {
  "mission_interfaces::srv",  // message namespace
  "GetLawnmowerPath_Response",  // message name
  2,  // number of fields
  sizeof(mission_interfaces::srv::GetLawnmowerPath_Response),
  false,  // has_any_key_member_
  GetLawnmowerPath_Response_message_member_array,  // message members
  GetLawnmowerPath_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  GetLawnmowerPath_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetLawnmowerPath_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetLawnmowerPath_Response_message_members,
  get_message_typesupport_handle_function,
  &mission_interfaces__srv__GetLawnmowerPath_Response__get_type_hash,
  &mission_interfaces__srv__GetLawnmowerPath_Response__get_type_description,
  &mission_interfaces__srv__GetLawnmowerPath_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace mission_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<mission_interfaces::srv::GetLawnmowerPath_Response>()
{
  return &::mission_interfaces::srv::rosidl_typesupport_introspection_cpp::GetLawnmowerPath_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, mission_interfaces, srv, GetLawnmowerPath_Response)() {
  return &::mission_interfaces::srv::rosidl_typesupport_introspection_cpp::GetLawnmowerPath_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__functions.h"
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace mission_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetLawnmowerPath_Event_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) mission_interfaces::srv::GetLawnmowerPath_Event(_init);
}

void GetLawnmowerPath_Event_fini_function(void * message_memory)
{
  auto typed_message = static_cast<mission_interfaces::srv::GetLawnmowerPath_Event *>(message_memory);
  typed_message->~GetLawnmowerPath_Event();
}

size_t size_function__GetLawnmowerPath_Event__request(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<mission_interfaces::srv::GetLawnmowerPath_Request> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetLawnmowerPath_Event__request(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<mission_interfaces::srv::GetLawnmowerPath_Request> *>(untyped_member);
  return &member[index];
}

void * get_function__GetLawnmowerPath_Event__request(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<mission_interfaces::srv::GetLawnmowerPath_Request> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetLawnmowerPath_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const mission_interfaces::srv::GetLawnmowerPath_Request *>(
    get_const_function__GetLawnmowerPath_Event__request(untyped_member, index));
  auto & value = *reinterpret_cast<mission_interfaces::srv::GetLawnmowerPath_Request *>(untyped_value);
  value = item;
}

void assign_function__GetLawnmowerPath_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<mission_interfaces::srv::GetLawnmowerPath_Request *>(
    get_function__GetLawnmowerPath_Event__request(untyped_member, index));
  const auto & value = *reinterpret_cast<const mission_interfaces::srv::GetLawnmowerPath_Request *>(untyped_value);
  item = value;
}

void resize_function__GetLawnmowerPath_Event__request(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<mission_interfaces::srv::GetLawnmowerPath_Request> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetLawnmowerPath_Event__response(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<mission_interfaces::srv::GetLawnmowerPath_Response> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetLawnmowerPath_Event__response(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<mission_interfaces::srv::GetLawnmowerPath_Response> *>(untyped_member);
  return &member[index];
}

void * get_function__GetLawnmowerPath_Event__response(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<mission_interfaces::srv::GetLawnmowerPath_Response> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetLawnmowerPath_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const mission_interfaces::srv::GetLawnmowerPath_Response *>(
    get_const_function__GetLawnmowerPath_Event__response(untyped_member, index));
  auto & value = *reinterpret_cast<mission_interfaces::srv::GetLawnmowerPath_Response *>(untyped_value);
  value = item;
}

void assign_function__GetLawnmowerPath_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<mission_interfaces::srv::GetLawnmowerPath_Response *>(
    get_function__GetLawnmowerPath_Event__response(untyped_member, index));
  const auto & value = *reinterpret_cast<const mission_interfaces::srv::GetLawnmowerPath_Response *>(untyped_value);
  item = value;
}

void resize_function__GetLawnmowerPath_Event__response(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<mission_interfaces::srv::GetLawnmowerPath_Response> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetLawnmowerPath_Event_message_member_array[3] = {
  {
    "info",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<service_msgs::msg::ServiceEventInfo>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces::srv::GetLawnmowerPath_Event, info),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "request",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<mission_interfaces::srv::GetLawnmowerPath_Request>(),  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(mission_interfaces::srv::GetLawnmowerPath_Event, request),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetLawnmowerPath_Event__request,  // size() function pointer
    get_const_function__GetLawnmowerPath_Event__request,  // get_const(index) function pointer
    get_function__GetLawnmowerPath_Event__request,  // get(index) function pointer
    fetch_function__GetLawnmowerPath_Event__request,  // fetch(index, &value) function pointer
    assign_function__GetLawnmowerPath_Event__request,  // assign(index, value) function pointer
    resize_function__GetLawnmowerPath_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<mission_interfaces::srv::GetLawnmowerPath_Response>(),  // members of sub message
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(mission_interfaces::srv::GetLawnmowerPath_Event, response),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetLawnmowerPath_Event__response,  // size() function pointer
    get_const_function__GetLawnmowerPath_Event__response,  // get_const(index) function pointer
    get_function__GetLawnmowerPath_Event__response,  // get(index) function pointer
    fetch_function__GetLawnmowerPath_Event__response,  // fetch(index, &value) function pointer
    assign_function__GetLawnmowerPath_Event__response,  // assign(index, value) function pointer
    resize_function__GetLawnmowerPath_Event__response  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetLawnmowerPath_Event_message_members = {
  "mission_interfaces::srv",  // message namespace
  "GetLawnmowerPath_Event",  // message name
  3,  // number of fields
  sizeof(mission_interfaces::srv::GetLawnmowerPath_Event),
  false,  // has_any_key_member_
  GetLawnmowerPath_Event_message_member_array,  // message members
  GetLawnmowerPath_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  GetLawnmowerPath_Event_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetLawnmowerPath_Event_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetLawnmowerPath_Event_message_members,
  get_message_typesupport_handle_function,
  &mission_interfaces__srv__GetLawnmowerPath_Event__get_type_hash,
  &mission_interfaces__srv__GetLawnmowerPath_Event__get_type_description,
  &mission_interfaces__srv__GetLawnmowerPath_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace mission_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<mission_interfaces::srv::GetLawnmowerPath_Event>()
{
  return &::mission_interfaces::srv::rosidl_typesupport_introspection_cpp::GetLawnmowerPath_Event_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, mission_interfaces, srv, GetLawnmowerPath_Event)() {
  return &::mission_interfaces::srv::rosidl_typesupport_introspection_cpp::GetLawnmowerPath_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__functions.h"
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace mission_interfaces
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers GetLawnmowerPath_service_members = {
  "mission_interfaces::srv",  // service namespace
  "GetLawnmowerPath",  // service name
  // the following fields are initialized below on first access
  // see get_service_type_support_handle<mission_interfaces::srv::GetLawnmowerPath>()
  nullptr,  // request message
  nullptr,  // response message
  nullptr,  // event message
};

static const rosidl_service_type_support_t GetLawnmowerPath_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetLawnmowerPath_service_members,
  get_service_typesupport_handle_function,
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<mission_interfaces::srv::GetLawnmowerPath_Request>(),
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<mission_interfaces::srv::GetLawnmowerPath_Response>(),
  ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<mission_interfaces::srv::GetLawnmowerPath_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<mission_interfaces::srv::GetLawnmowerPath>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<mission_interfaces::srv::GetLawnmowerPath>,
  &mission_interfaces__srv__GetLawnmowerPath__get_type_hash,
  &mission_interfaces__srv__GetLawnmowerPath__get_type_description,
  &mission_interfaces__srv__GetLawnmowerPath__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace mission_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<mission_interfaces::srv::GetLawnmowerPath>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::mission_interfaces::srv::rosidl_typesupport_introspection_cpp::GetLawnmowerPath_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure all of the service_members are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr ||
    service_members->event_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::mission_interfaces::srv::GetLawnmowerPath_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::mission_interfaces::srv::GetLawnmowerPath_Response
      >()->data
      );
    // initialize the event_members_ with the static function from the external library
    service_members->event_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::mission_interfaces::srv::GetLawnmowerPath_Event
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, mission_interfaces, srv, GetLawnmowerPath)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<mission_interfaces::srv::GetLawnmowerPath>();
}

#ifdef __cplusplus
}
#endif
