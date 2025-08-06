// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from mission_interfaces:srv/GetLawnmowerPath.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "mission_interfaces/srv/detail/get_lawnmower_path__rosidl_typesupport_introspection_c.h"
#include "mission_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "mission_interfaces/srv/detail/get_lawnmower_path__functions.h"
#include "mission_interfaces/srv/detail/get_lawnmower_path__struct.h"


// Include directives for member types
// Member `polygon_x`
// Member `polygon_y`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  mission_interfaces__srv__GetLawnmowerPath_Request__init(message_memory);
}

void mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_fini_function(void * message_memory)
{
  mission_interfaces__srv__GetLawnmowerPath_Request__fini(message_memory);
}

size_t mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__size_function__GetLawnmowerPath_Request__polygon_x(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Request__polygon_x(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Request__polygon_x(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__fetch_function__GetLawnmowerPath_Request__polygon_x(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Request__polygon_x(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__assign_function__GetLawnmowerPath_Request__polygon_x(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Request__polygon_x(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__resize_function__GetLawnmowerPath_Request__polygon_x(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__size_function__GetLawnmowerPath_Request__polygon_y(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Request__polygon_y(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Request__polygon_y(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__fetch_function__GetLawnmowerPath_Request__polygon_y(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Request__polygon_y(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__assign_function__GetLawnmowerPath_Request__polygon_y(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Request__polygon_y(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__resize_function__GetLawnmowerPath_Request__polygon_y(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_message_member_array[5] = {
  {
    "polygon_x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces__srv__GetLawnmowerPath_Request, polygon_x),  // bytes offset in struct
    NULL,  // default value
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__size_function__GetLawnmowerPath_Request__polygon_x,  // size() function pointer
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Request__polygon_x,  // get_const(index) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Request__polygon_x,  // get(index) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__fetch_function__GetLawnmowerPath_Request__polygon_x,  // fetch(index, &value) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__assign_function__GetLawnmowerPath_Request__polygon_x,  // assign(index, value) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__resize_function__GetLawnmowerPath_Request__polygon_x  // resize(index) function pointer
  },
  {
    "polygon_y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces__srv__GetLawnmowerPath_Request, polygon_y),  // bytes offset in struct
    NULL,  // default value
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__size_function__GetLawnmowerPath_Request__polygon_y,  // size() function pointer
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Request__polygon_y,  // get_const(index) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Request__polygon_y,  // get(index) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__fetch_function__GetLawnmowerPath_Request__polygon_y,  // fetch(index, &value) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__assign_function__GetLawnmowerPath_Request__polygon_y,  // assign(index, value) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__resize_function__GetLawnmowerPath_Request__polygon_y  // resize(index) function pointer
  },
  {
    "safe_margin",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces__srv__GetLawnmowerPath_Request, safe_margin),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "spacing",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces__srv__GetLawnmowerPath_Request, spacing),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "angle",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces__srv__GetLawnmowerPath_Request, angle),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_message_members = {
  "mission_interfaces__srv",  // message namespace
  "GetLawnmowerPath_Request",  // message name
  5,  // number of fields
  sizeof(mission_interfaces__srv__GetLawnmowerPath_Request),
  false,  // has_any_key_member_
  mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_message_member_array,  // message members
  mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_message_type_support_handle = {
  0,
  &mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_message_members,
  get_message_typesupport_handle_function,
  &mission_interfaces__srv__GetLawnmowerPath_Request__get_type_hash,
  &mission_interfaces__srv__GetLawnmowerPath_Request__get_type_description,
  &mission_interfaces__srv__GetLawnmowerPath_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_mission_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mission_interfaces, srv, GetLawnmowerPath_Request)() {
  if (!mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_message_type_support_handle.typesupport_identifier) {
    mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__rosidl_typesupport_introspection_c.h"
// already included above
// #include "mission_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__functions.h"
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__struct.h"


// Include directives for member types
// Member `waypoint_x`
// Member `waypoint_y`
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  mission_interfaces__srv__GetLawnmowerPath_Response__init(message_memory);
}

void mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_fini_function(void * message_memory)
{
  mission_interfaces__srv__GetLawnmowerPath_Response__fini(message_memory);
}

size_t mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__size_function__GetLawnmowerPath_Response__waypoint_x(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Response__waypoint_x(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Response__waypoint_x(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__fetch_function__GetLawnmowerPath_Response__waypoint_x(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Response__waypoint_x(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__assign_function__GetLawnmowerPath_Response__waypoint_x(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Response__waypoint_x(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__resize_function__GetLawnmowerPath_Response__waypoint_x(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__size_function__GetLawnmowerPath_Response__waypoint_y(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Response__waypoint_y(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Response__waypoint_y(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__fetch_function__GetLawnmowerPath_Response__waypoint_y(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Response__waypoint_y(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__assign_function__GetLawnmowerPath_Response__waypoint_y(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Response__waypoint_y(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__resize_function__GetLawnmowerPath_Response__waypoint_y(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_message_member_array[2] = {
  {
    "waypoint_x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces__srv__GetLawnmowerPath_Response, waypoint_x),  // bytes offset in struct
    NULL,  // default value
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__size_function__GetLawnmowerPath_Response__waypoint_x,  // size() function pointer
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Response__waypoint_x,  // get_const(index) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Response__waypoint_x,  // get(index) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__fetch_function__GetLawnmowerPath_Response__waypoint_x,  // fetch(index, &value) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__assign_function__GetLawnmowerPath_Response__waypoint_x,  // assign(index, value) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__resize_function__GetLawnmowerPath_Response__waypoint_x  // resize(index) function pointer
  },
  {
    "waypoint_y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces__srv__GetLawnmowerPath_Response, waypoint_y),  // bytes offset in struct
    NULL,  // default value
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__size_function__GetLawnmowerPath_Response__waypoint_y,  // size() function pointer
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Response__waypoint_y,  // get_const(index) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Response__waypoint_y,  // get(index) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__fetch_function__GetLawnmowerPath_Response__waypoint_y,  // fetch(index, &value) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__assign_function__GetLawnmowerPath_Response__waypoint_y,  // assign(index, value) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__resize_function__GetLawnmowerPath_Response__waypoint_y  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_message_members = {
  "mission_interfaces__srv",  // message namespace
  "GetLawnmowerPath_Response",  // message name
  2,  // number of fields
  sizeof(mission_interfaces__srv__GetLawnmowerPath_Response),
  false,  // has_any_key_member_
  mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_message_member_array,  // message members
  mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_message_type_support_handle = {
  0,
  &mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_message_members,
  get_message_typesupport_handle_function,
  &mission_interfaces__srv__GetLawnmowerPath_Response__get_type_hash,
  &mission_interfaces__srv__GetLawnmowerPath_Response__get_type_description,
  &mission_interfaces__srv__GetLawnmowerPath_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_mission_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mission_interfaces, srv, GetLawnmowerPath_Response)() {
  if (!mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_message_type_support_handle.typesupport_identifier) {
    mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__rosidl_typesupport_introspection_c.h"
// already included above
// #include "mission_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__functions.h"
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "mission_interfaces/srv/get_lawnmower_path.h"
// Member `request`
// Member `response`
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  mission_interfaces__srv__GetLawnmowerPath_Event__init(message_memory);
}

void mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_fini_function(void * message_memory)
{
  mission_interfaces__srv__GetLawnmowerPath_Event__fini(message_memory);
}

size_t mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__size_function__GetLawnmowerPath_Event__request(
  const void * untyped_member)
{
  const mission_interfaces__srv__GetLawnmowerPath_Request__Sequence * member =
    (const mission_interfaces__srv__GetLawnmowerPath_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Event__request(
  const void * untyped_member, size_t index)
{
  const mission_interfaces__srv__GetLawnmowerPath_Request__Sequence * member =
    (const mission_interfaces__srv__GetLawnmowerPath_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Event__request(
  void * untyped_member, size_t index)
{
  mission_interfaces__srv__GetLawnmowerPath_Request__Sequence * member =
    (mission_interfaces__srv__GetLawnmowerPath_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__fetch_function__GetLawnmowerPath_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const mission_interfaces__srv__GetLawnmowerPath_Request * item =
    ((const mission_interfaces__srv__GetLawnmowerPath_Request *)
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Event__request(untyped_member, index));
  mission_interfaces__srv__GetLawnmowerPath_Request * value =
    (mission_interfaces__srv__GetLawnmowerPath_Request *)(untyped_value);
  *value = *item;
}

void mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__assign_function__GetLawnmowerPath_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  mission_interfaces__srv__GetLawnmowerPath_Request * item =
    ((mission_interfaces__srv__GetLawnmowerPath_Request *)
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Event__request(untyped_member, index));
  const mission_interfaces__srv__GetLawnmowerPath_Request * value =
    (const mission_interfaces__srv__GetLawnmowerPath_Request *)(untyped_value);
  *item = *value;
}

bool mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__resize_function__GetLawnmowerPath_Event__request(
  void * untyped_member, size_t size)
{
  mission_interfaces__srv__GetLawnmowerPath_Request__Sequence * member =
    (mission_interfaces__srv__GetLawnmowerPath_Request__Sequence *)(untyped_member);
  mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__fini(member);
  return mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__init(member, size);
}

size_t mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__size_function__GetLawnmowerPath_Event__response(
  const void * untyped_member)
{
  const mission_interfaces__srv__GetLawnmowerPath_Response__Sequence * member =
    (const mission_interfaces__srv__GetLawnmowerPath_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Event__response(
  const void * untyped_member, size_t index)
{
  const mission_interfaces__srv__GetLawnmowerPath_Response__Sequence * member =
    (const mission_interfaces__srv__GetLawnmowerPath_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Event__response(
  void * untyped_member, size_t index)
{
  mission_interfaces__srv__GetLawnmowerPath_Response__Sequence * member =
    (mission_interfaces__srv__GetLawnmowerPath_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__fetch_function__GetLawnmowerPath_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const mission_interfaces__srv__GetLawnmowerPath_Response * item =
    ((const mission_interfaces__srv__GetLawnmowerPath_Response *)
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Event__response(untyped_member, index));
  mission_interfaces__srv__GetLawnmowerPath_Response * value =
    (mission_interfaces__srv__GetLawnmowerPath_Response *)(untyped_value);
  *value = *item;
}

void mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__assign_function__GetLawnmowerPath_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  mission_interfaces__srv__GetLawnmowerPath_Response * item =
    ((mission_interfaces__srv__GetLawnmowerPath_Response *)
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Event__response(untyped_member, index));
  const mission_interfaces__srv__GetLawnmowerPath_Response * value =
    (const mission_interfaces__srv__GetLawnmowerPath_Response *)(untyped_value);
  *item = *value;
}

bool mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__resize_function__GetLawnmowerPath_Event__response(
  void * untyped_member, size_t size)
{
  mission_interfaces__srv__GetLawnmowerPath_Response__Sequence * member =
    (mission_interfaces__srv__GetLawnmowerPath_Response__Sequence *)(untyped_member);
  mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__fini(member);
  return mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(mission_interfaces__srv__GetLawnmowerPath_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(mission_interfaces__srv__GetLawnmowerPath_Event, request),  // bytes offset in struct
    NULL,  // default value
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__size_function__GetLawnmowerPath_Event__request,  // size() function pointer
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Event__request,  // get_const(index) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Event__request,  // get(index) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__fetch_function__GetLawnmowerPath_Event__request,  // fetch(index, &value) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__assign_function__GetLawnmowerPath_Event__request,  // assign(index, value) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__resize_function__GetLawnmowerPath_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(mission_interfaces__srv__GetLawnmowerPath_Event, response),  // bytes offset in struct
    NULL,  // default value
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__size_function__GetLawnmowerPath_Event__response,  // size() function pointer
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__get_const_function__GetLawnmowerPath_Event__response,  // get_const(index) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__get_function__GetLawnmowerPath_Event__response,  // get(index) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__fetch_function__GetLawnmowerPath_Event__response,  // fetch(index, &value) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__assign_function__GetLawnmowerPath_Event__response,  // assign(index, value) function pointer
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__resize_function__GetLawnmowerPath_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_message_members = {
  "mission_interfaces__srv",  // message namespace
  "GetLawnmowerPath_Event",  // message name
  3,  // number of fields
  sizeof(mission_interfaces__srv__GetLawnmowerPath_Event),
  false,  // has_any_key_member_
  mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_message_member_array,  // message members
  mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_message_type_support_handle = {
  0,
  &mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_message_members,
  get_message_typesupport_handle_function,
  &mission_interfaces__srv__GetLawnmowerPath_Event__get_type_hash,
  &mission_interfaces__srv__GetLawnmowerPath_Event__get_type_description,
  &mission_interfaces__srv__GetLawnmowerPath_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_mission_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mission_interfaces, srv, GetLawnmowerPath_Event)() {
  mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mission_interfaces, srv, GetLawnmowerPath_Request)();
  mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mission_interfaces, srv, GetLawnmowerPath_Response)();
  if (!mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_message_type_support_handle.typesupport_identifier) {
    mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "mission_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers mission_interfaces__srv__detail__get_lawnmower_path__rosidl_typesupport_introspection_c__GetLawnmowerPath_service_members = {
  "mission_interfaces__srv",  // service namespace
  "GetLawnmowerPath",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // mission_interfaces__srv__detail__get_lawnmower_path__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_message_type_support_handle,
  NULL,  // response message
  // mission_interfaces__srv__detail__get_lawnmower_path__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_message_type_support_handle
  NULL  // event_message
  // mission_interfaces__srv__detail__get_lawnmower_path__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_message_type_support_handle
};


static rosidl_service_type_support_t mission_interfaces__srv__detail__get_lawnmower_path__rosidl_typesupport_introspection_c__GetLawnmowerPath_service_type_support_handle = {
  0,
  &mission_interfaces__srv__detail__get_lawnmower_path__rosidl_typesupport_introspection_c__GetLawnmowerPath_service_members,
  get_service_typesupport_handle_function,
  &mission_interfaces__srv__GetLawnmowerPath_Request__rosidl_typesupport_introspection_c__GetLawnmowerPath_Request_message_type_support_handle,
  &mission_interfaces__srv__GetLawnmowerPath_Response__rosidl_typesupport_introspection_c__GetLawnmowerPath_Response_message_type_support_handle,
  &mission_interfaces__srv__GetLawnmowerPath_Event__rosidl_typesupport_introspection_c__GetLawnmowerPath_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    mission_interfaces,
    srv,
    GetLawnmowerPath
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    mission_interfaces,
    srv,
    GetLawnmowerPath
  ),
  &mission_interfaces__srv__GetLawnmowerPath__get_type_hash,
  &mission_interfaces__srv__GetLawnmowerPath__get_type_description,
  &mission_interfaces__srv__GetLawnmowerPath__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mission_interfaces, srv, GetLawnmowerPath_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mission_interfaces, srv, GetLawnmowerPath_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mission_interfaces, srv, GetLawnmowerPath_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_mission_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mission_interfaces, srv, GetLawnmowerPath)(void) {
  if (!mission_interfaces__srv__detail__get_lawnmower_path__rosidl_typesupport_introspection_c__GetLawnmowerPath_service_type_support_handle.typesupport_identifier) {
    mission_interfaces__srv__detail__get_lawnmower_path__rosidl_typesupport_introspection_c__GetLawnmowerPath_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)mission_interfaces__srv__detail__get_lawnmower_path__rosidl_typesupport_introspection_c__GetLawnmowerPath_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mission_interfaces, srv, GetLawnmowerPath_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mission_interfaces, srv, GetLawnmowerPath_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, mission_interfaces, srv, GetLawnmowerPath_Event)()->data;
  }

  return &mission_interfaces__srv__detail__get_lawnmower_path__rosidl_typesupport_introspection_c__GetLawnmowerPath_service_type_support_handle;
}
