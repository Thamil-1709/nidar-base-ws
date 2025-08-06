// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from mission_interfaces:srv/GetLawnmowerPath.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "mission_interfaces/srv/get_lawnmower_path.hpp"


#ifndef MISSION_INTERFACES__SRV__DETAIL__GET_LAWNMOWER_PATH__TRAITS_HPP_
#define MISSION_INTERFACES__SRV__DETAIL__GET_LAWNMOWER_PATH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "mission_interfaces/srv/detail/get_lawnmower_path__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace mission_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetLawnmowerPath_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: polygon_x
  {
    if (msg.polygon_x.size() == 0) {
      out << "polygon_x: []";
    } else {
      out << "polygon_x: [";
      size_t pending_items = msg.polygon_x.size();
      for (auto item : msg.polygon_x) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: polygon_y
  {
    if (msg.polygon_y.size() == 0) {
      out << "polygon_y: []";
    } else {
      out << "polygon_y: [";
      size_t pending_items = msg.polygon_y.size();
      for (auto item : msg.polygon_y) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: safe_margin
  {
    out << "safe_margin: ";
    rosidl_generator_traits::value_to_yaml(msg.safe_margin, out);
    out << ", ";
  }

  // member: spacing
  {
    out << "spacing: ";
    rosidl_generator_traits::value_to_yaml(msg.spacing, out);
    out << ", ";
  }

  // member: angle
  {
    out << "angle: ";
    rosidl_generator_traits::value_to_yaml(msg.angle, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetLawnmowerPath_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: polygon_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.polygon_x.size() == 0) {
      out << "polygon_x: []\n";
    } else {
      out << "polygon_x:\n";
      for (auto item : msg.polygon_x) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: polygon_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.polygon_y.size() == 0) {
      out << "polygon_y: []\n";
    } else {
      out << "polygon_y:\n";
      for (auto item : msg.polygon_y) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: safe_margin
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "safe_margin: ";
    rosidl_generator_traits::value_to_yaml(msg.safe_margin, out);
    out << "\n";
  }

  // member: spacing
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "spacing: ";
    rosidl_generator_traits::value_to_yaml(msg.spacing, out);
    out << "\n";
  }

  // member: angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angle: ";
    rosidl_generator_traits::value_to_yaml(msg.angle, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetLawnmowerPath_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace mission_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use mission_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const mission_interfaces::srv::GetLawnmowerPath_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  mission_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use mission_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const mission_interfaces::srv::GetLawnmowerPath_Request & msg)
{
  return mission_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<mission_interfaces::srv::GetLawnmowerPath_Request>()
{
  return "mission_interfaces::srv::GetLawnmowerPath_Request";
}

template<>
inline const char * name<mission_interfaces::srv::GetLawnmowerPath_Request>()
{
  return "mission_interfaces/srv/GetLawnmowerPath_Request";
}

template<>
struct has_fixed_size<mission_interfaces::srv::GetLawnmowerPath_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<mission_interfaces::srv::GetLawnmowerPath_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<mission_interfaces::srv::GetLawnmowerPath_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace mission_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetLawnmowerPath_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: waypoint_x
  {
    if (msg.waypoint_x.size() == 0) {
      out << "waypoint_x: []";
    } else {
      out << "waypoint_x: [";
      size_t pending_items = msg.waypoint_x.size();
      for (auto item : msg.waypoint_x) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: waypoint_y
  {
    if (msg.waypoint_y.size() == 0) {
      out << "waypoint_y: []";
    } else {
      out << "waypoint_y: [";
      size_t pending_items = msg.waypoint_y.size();
      for (auto item : msg.waypoint_y) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetLawnmowerPath_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: waypoint_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.waypoint_x.size() == 0) {
      out << "waypoint_x: []\n";
    } else {
      out << "waypoint_x:\n";
      for (auto item : msg.waypoint_x) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: waypoint_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.waypoint_y.size() == 0) {
      out << "waypoint_y: []\n";
    } else {
      out << "waypoint_y:\n";
      for (auto item : msg.waypoint_y) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetLawnmowerPath_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace mission_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use mission_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const mission_interfaces::srv::GetLawnmowerPath_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  mission_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use mission_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const mission_interfaces::srv::GetLawnmowerPath_Response & msg)
{
  return mission_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<mission_interfaces::srv::GetLawnmowerPath_Response>()
{
  return "mission_interfaces::srv::GetLawnmowerPath_Response";
}

template<>
inline const char * name<mission_interfaces::srv::GetLawnmowerPath_Response>()
{
  return "mission_interfaces/srv/GetLawnmowerPath_Response";
}

template<>
struct has_fixed_size<mission_interfaces::srv::GetLawnmowerPath_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<mission_interfaces::srv::GetLawnmowerPath_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<mission_interfaces::srv::GetLawnmowerPath_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace mission_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetLawnmowerPath_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetLawnmowerPath_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetLawnmowerPath_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace mission_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use mission_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const mission_interfaces::srv::GetLawnmowerPath_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  mission_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use mission_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const mission_interfaces::srv::GetLawnmowerPath_Event & msg)
{
  return mission_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<mission_interfaces::srv::GetLawnmowerPath_Event>()
{
  return "mission_interfaces::srv::GetLawnmowerPath_Event";
}

template<>
inline const char * name<mission_interfaces::srv::GetLawnmowerPath_Event>()
{
  return "mission_interfaces/srv/GetLawnmowerPath_Event";
}

template<>
struct has_fixed_size<mission_interfaces::srv::GetLawnmowerPath_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<mission_interfaces::srv::GetLawnmowerPath_Event>
  : std::integral_constant<bool, has_bounded_size<mission_interfaces::srv::GetLawnmowerPath_Request>::value && has_bounded_size<mission_interfaces::srv::GetLawnmowerPath_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<mission_interfaces::srv::GetLawnmowerPath_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<mission_interfaces::srv::GetLawnmowerPath>()
{
  return "mission_interfaces::srv::GetLawnmowerPath";
}

template<>
inline const char * name<mission_interfaces::srv::GetLawnmowerPath>()
{
  return "mission_interfaces/srv/GetLawnmowerPath";
}

template<>
struct has_fixed_size<mission_interfaces::srv::GetLawnmowerPath>
  : std::integral_constant<
    bool,
    has_fixed_size<mission_interfaces::srv::GetLawnmowerPath_Request>::value &&
    has_fixed_size<mission_interfaces::srv::GetLawnmowerPath_Response>::value
  >
{
};

template<>
struct has_bounded_size<mission_interfaces::srv::GetLawnmowerPath>
  : std::integral_constant<
    bool,
    has_bounded_size<mission_interfaces::srv::GetLawnmowerPath_Request>::value &&
    has_bounded_size<mission_interfaces::srv::GetLawnmowerPath_Response>::value
  >
{
};

template<>
struct is_service<mission_interfaces::srv::GetLawnmowerPath>
  : std::true_type
{
};

template<>
struct is_service_request<mission_interfaces::srv::GetLawnmowerPath_Request>
  : std::true_type
{
};

template<>
struct is_service_response<mission_interfaces::srv::GetLawnmowerPath_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // MISSION_INTERFACES__SRV__DETAIL__GET_LAWNMOWER_PATH__TRAITS_HPP_
