// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from mission_interfaces:srv/GetLawnmowerPath.idl
// generated code does not contain a copyright notice

#include "mission_interfaces/srv/detail/get_lawnmower_path__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_mission_interfaces
const rosidl_type_hash_t *
mission_interfaces__srv__GetLawnmowerPath__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x55, 0x5e, 0x05, 0xf9, 0x13, 0xa9, 0x93, 0xba,
      0x74, 0xa9, 0x40, 0x8c, 0xc1, 0xba, 0xd8, 0x4a,
      0xcc, 0xb9, 0xfc, 0x0d, 0xce, 0x1a, 0xff, 0xf6,
      0x5f, 0x40, 0xdc, 0x39, 0x61, 0x75, 0xe8, 0x1b,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_mission_interfaces
const rosidl_type_hash_t *
mission_interfaces__srv__GetLawnmowerPath_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x61, 0x43, 0xd1, 0xce, 0xcc, 0x5f, 0xdb, 0xf6,
      0x05, 0x59, 0xca, 0x97, 0x97, 0x89, 0xe5, 0x23,
      0x56, 0xed, 0x1d, 0x56, 0xc2, 0x47, 0x8d, 0x51,
      0xbb, 0x18, 0x8a, 0xbf, 0xed, 0xa3, 0xd3, 0x8f,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_mission_interfaces
const rosidl_type_hash_t *
mission_interfaces__srv__GetLawnmowerPath_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x99, 0xe3, 0x29, 0x13, 0x2f, 0x10, 0xd8, 0xa3,
      0x62, 0xb3, 0x8f, 0x7a, 0x82, 0x14, 0x14, 0xfc,
      0x20, 0xf4, 0x94, 0xca, 0xdc, 0xe2, 0x51, 0x15,
      0xb6, 0xb1, 0x01, 0x8b, 0x9f, 0x01, 0xc6, 0xd0,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_mission_interfaces
const rosidl_type_hash_t *
mission_interfaces__srv__GetLawnmowerPath_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x2d, 0x40, 0x91, 0xfe, 0xe4, 0x4c, 0xa8, 0x6e,
      0x8a, 0xb3, 0x51, 0x8b, 0xb4, 0x9d, 0xea, 0xe2,
      0x14, 0x7c, 0xb4, 0x8e, 0xb3, 0x7e, 0x9d, 0xa6,
      0x8a, 0x53, 0xde, 0x1d, 0x42, 0x6b, 0x7d, 0x40,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char mission_interfaces__srv__GetLawnmowerPath__TYPE_NAME[] = "mission_interfaces/srv/GetLawnmowerPath";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char mission_interfaces__srv__GetLawnmowerPath_Event__TYPE_NAME[] = "mission_interfaces/srv/GetLawnmowerPath_Event";
static char mission_interfaces__srv__GetLawnmowerPath_Request__TYPE_NAME[] = "mission_interfaces/srv/GetLawnmowerPath_Request";
static char mission_interfaces__srv__GetLawnmowerPath_Response__TYPE_NAME[] = "mission_interfaces/srv/GetLawnmowerPath_Response";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char mission_interfaces__srv__GetLawnmowerPath__FIELD_NAME__request_message[] = "request_message";
static char mission_interfaces__srv__GetLawnmowerPath__FIELD_NAME__response_message[] = "response_message";
static char mission_interfaces__srv__GetLawnmowerPath__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field mission_interfaces__srv__GetLawnmowerPath__FIELDS[] = {
  {
    {mission_interfaces__srv__GetLawnmowerPath__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {mission_interfaces__srv__GetLawnmowerPath_Request__TYPE_NAME, 47, 47},
    },
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {mission_interfaces__srv__GetLawnmowerPath_Response__TYPE_NAME, 48, 48},
    },
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {mission_interfaces__srv__GetLawnmowerPath_Event__TYPE_NAME, 45, 45},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription mission_interfaces__srv__GetLawnmowerPath__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath_Event__TYPE_NAME, 45, 45},
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath_Request__TYPE_NAME, 47, 47},
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath_Response__TYPE_NAME, 48, 48},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
mission_interfaces__srv__GetLawnmowerPath__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {mission_interfaces__srv__GetLawnmowerPath__TYPE_NAME, 39, 39},
      {mission_interfaces__srv__GetLawnmowerPath__FIELDS, 3, 3},
    },
    {mission_interfaces__srv__GetLawnmowerPath__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = mission_interfaces__srv__GetLawnmowerPath_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = mission_interfaces__srv__GetLawnmowerPath_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = mission_interfaces__srv__GetLawnmowerPath_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char mission_interfaces__srv__GetLawnmowerPath_Request__FIELD_NAME__polygon_x[] = "polygon_x";
static char mission_interfaces__srv__GetLawnmowerPath_Request__FIELD_NAME__polygon_y[] = "polygon_y";
static char mission_interfaces__srv__GetLawnmowerPath_Request__FIELD_NAME__safe_margin[] = "safe_margin";
static char mission_interfaces__srv__GetLawnmowerPath_Request__FIELD_NAME__spacing[] = "spacing";
static char mission_interfaces__srv__GetLawnmowerPath_Request__FIELD_NAME__angle[] = "angle";

static rosidl_runtime_c__type_description__Field mission_interfaces__srv__GetLawnmowerPath_Request__FIELDS[] = {
  {
    {mission_interfaces__srv__GetLawnmowerPath_Request__FIELD_NAME__polygon_x, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath_Request__FIELD_NAME__polygon_y, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath_Request__FIELD_NAME__safe_margin, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath_Request__FIELD_NAME__spacing, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath_Request__FIELD_NAME__angle, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
mission_interfaces__srv__GetLawnmowerPath_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {mission_interfaces__srv__GetLawnmowerPath_Request__TYPE_NAME, 47, 47},
      {mission_interfaces__srv__GetLawnmowerPath_Request__FIELDS, 5, 5},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char mission_interfaces__srv__GetLawnmowerPath_Response__FIELD_NAME__waypoint_x[] = "waypoint_x";
static char mission_interfaces__srv__GetLawnmowerPath_Response__FIELD_NAME__waypoint_y[] = "waypoint_y";

static rosidl_runtime_c__type_description__Field mission_interfaces__srv__GetLawnmowerPath_Response__FIELDS[] = {
  {
    {mission_interfaces__srv__GetLawnmowerPath_Response__FIELD_NAME__waypoint_x, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath_Response__FIELD_NAME__waypoint_y, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
mission_interfaces__srv__GetLawnmowerPath_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {mission_interfaces__srv__GetLawnmowerPath_Response__TYPE_NAME, 48, 48},
      {mission_interfaces__srv__GetLawnmowerPath_Response__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char mission_interfaces__srv__GetLawnmowerPath_Event__FIELD_NAME__info[] = "info";
static char mission_interfaces__srv__GetLawnmowerPath_Event__FIELD_NAME__request[] = "request";
static char mission_interfaces__srv__GetLawnmowerPath_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field mission_interfaces__srv__GetLawnmowerPath_Event__FIELDS[] = {
  {
    {mission_interfaces__srv__GetLawnmowerPath_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {mission_interfaces__srv__GetLawnmowerPath_Request__TYPE_NAME, 47, 47},
    },
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {mission_interfaces__srv__GetLawnmowerPath_Response__TYPE_NAME, 48, 48},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription mission_interfaces__srv__GetLawnmowerPath_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath_Request__TYPE_NAME, 47, 47},
    {NULL, 0, 0},
  },
  {
    {mission_interfaces__srv__GetLawnmowerPath_Response__TYPE_NAME, 48, 48},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
mission_interfaces__srv__GetLawnmowerPath_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {mission_interfaces__srv__GetLawnmowerPath_Event__TYPE_NAME, 45, 45},
      {mission_interfaces__srv__GetLawnmowerPath_Event__FIELDS, 3, 3},
    },
    {mission_interfaces__srv__GetLawnmowerPath_Event__REFERENCED_TYPE_DESCRIPTIONS, 4, 4},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = mission_interfaces__srv__GetLawnmowerPath_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = mission_interfaces__srv__GetLawnmowerPath_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Request\n"
  "float64[] polygon_x\n"
  "float64[] polygon_y\n"
  "float64 safe_margin\n"
  "float64 spacing\n"
  "float64 angle\n"
  "\n"
  "---\n"
  "# Response\n"
  "float64[] waypoint_x\n"
  "float64[] waypoint_y";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
mission_interfaces__srv__GetLawnmowerPath__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {mission_interfaces__srv__GetLawnmowerPath__TYPE_NAME, 39, 39},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 157, 157},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
mission_interfaces__srv__GetLawnmowerPath_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {mission_interfaces__srv__GetLawnmowerPath_Request__TYPE_NAME, 47, 47},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
mission_interfaces__srv__GetLawnmowerPath_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {mission_interfaces__srv__GetLawnmowerPath_Response__TYPE_NAME, 48, 48},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
mission_interfaces__srv__GetLawnmowerPath_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {mission_interfaces__srv__GetLawnmowerPath_Event__TYPE_NAME, 45, 45},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
mission_interfaces__srv__GetLawnmowerPath__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *mission_interfaces__srv__GetLawnmowerPath__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *mission_interfaces__srv__GetLawnmowerPath_Event__get_individual_type_description_source(NULL);
    sources[3] = *mission_interfaces__srv__GetLawnmowerPath_Request__get_individual_type_description_source(NULL);
    sources[4] = *mission_interfaces__srv__GetLawnmowerPath_Response__get_individual_type_description_source(NULL);
    sources[5] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
mission_interfaces__srv__GetLawnmowerPath_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *mission_interfaces__srv__GetLawnmowerPath_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
mission_interfaces__srv__GetLawnmowerPath_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *mission_interfaces__srv__GetLawnmowerPath_Response__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
mission_interfaces__srv__GetLawnmowerPath_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[5];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 5, 5};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *mission_interfaces__srv__GetLawnmowerPath_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *mission_interfaces__srv__GetLawnmowerPath_Request__get_individual_type_description_source(NULL);
    sources[3] = *mission_interfaces__srv__GetLawnmowerPath_Response__get_individual_type_description_source(NULL);
    sources[4] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
