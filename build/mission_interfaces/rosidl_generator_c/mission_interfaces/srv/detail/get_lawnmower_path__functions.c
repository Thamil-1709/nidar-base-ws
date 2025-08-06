// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from mission_interfaces:srv/GetLawnmowerPath.idl
// generated code does not contain a copyright notice
#include "mission_interfaces/srv/detail/get_lawnmower_path__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `polygon_x`
// Member `polygon_y`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
mission_interfaces__srv__GetLawnmowerPath_Request__init(mission_interfaces__srv__GetLawnmowerPath_Request * msg)
{
  if (!msg) {
    return false;
  }
  // polygon_x
  if (!rosidl_runtime_c__double__Sequence__init(&msg->polygon_x, 0)) {
    mission_interfaces__srv__GetLawnmowerPath_Request__fini(msg);
    return false;
  }
  // polygon_y
  if (!rosidl_runtime_c__double__Sequence__init(&msg->polygon_y, 0)) {
    mission_interfaces__srv__GetLawnmowerPath_Request__fini(msg);
    return false;
  }
  // safe_margin
  // spacing
  // angle
  return true;
}

void
mission_interfaces__srv__GetLawnmowerPath_Request__fini(mission_interfaces__srv__GetLawnmowerPath_Request * msg)
{
  if (!msg) {
    return;
  }
  // polygon_x
  rosidl_runtime_c__double__Sequence__fini(&msg->polygon_x);
  // polygon_y
  rosidl_runtime_c__double__Sequence__fini(&msg->polygon_y);
  // safe_margin
  // spacing
  // angle
}

bool
mission_interfaces__srv__GetLawnmowerPath_Request__are_equal(const mission_interfaces__srv__GetLawnmowerPath_Request * lhs, const mission_interfaces__srv__GetLawnmowerPath_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // polygon_x
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->polygon_x), &(rhs->polygon_x)))
  {
    return false;
  }
  // polygon_y
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->polygon_y), &(rhs->polygon_y)))
  {
    return false;
  }
  // safe_margin
  if (lhs->safe_margin != rhs->safe_margin) {
    return false;
  }
  // spacing
  if (lhs->spacing != rhs->spacing) {
    return false;
  }
  // angle
  if (lhs->angle != rhs->angle) {
    return false;
  }
  return true;
}

bool
mission_interfaces__srv__GetLawnmowerPath_Request__copy(
  const mission_interfaces__srv__GetLawnmowerPath_Request * input,
  mission_interfaces__srv__GetLawnmowerPath_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // polygon_x
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->polygon_x), &(output->polygon_x)))
  {
    return false;
  }
  // polygon_y
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->polygon_y), &(output->polygon_y)))
  {
    return false;
  }
  // safe_margin
  output->safe_margin = input->safe_margin;
  // spacing
  output->spacing = input->spacing;
  // angle
  output->angle = input->angle;
  return true;
}

mission_interfaces__srv__GetLawnmowerPath_Request *
mission_interfaces__srv__GetLawnmowerPath_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mission_interfaces__srv__GetLawnmowerPath_Request * msg = (mission_interfaces__srv__GetLawnmowerPath_Request *)allocator.allocate(sizeof(mission_interfaces__srv__GetLawnmowerPath_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(mission_interfaces__srv__GetLawnmowerPath_Request));
  bool success = mission_interfaces__srv__GetLawnmowerPath_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
mission_interfaces__srv__GetLawnmowerPath_Request__destroy(mission_interfaces__srv__GetLawnmowerPath_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    mission_interfaces__srv__GetLawnmowerPath_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__init(mission_interfaces__srv__GetLawnmowerPath_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mission_interfaces__srv__GetLawnmowerPath_Request * data = NULL;

  if (size) {
    data = (mission_interfaces__srv__GetLawnmowerPath_Request *)allocator.zero_allocate(size, sizeof(mission_interfaces__srv__GetLawnmowerPath_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = mission_interfaces__srv__GetLawnmowerPath_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        mission_interfaces__srv__GetLawnmowerPath_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__fini(mission_interfaces__srv__GetLawnmowerPath_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      mission_interfaces__srv__GetLawnmowerPath_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

mission_interfaces__srv__GetLawnmowerPath_Request__Sequence *
mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mission_interfaces__srv__GetLawnmowerPath_Request__Sequence * array = (mission_interfaces__srv__GetLawnmowerPath_Request__Sequence *)allocator.allocate(sizeof(mission_interfaces__srv__GetLawnmowerPath_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__destroy(mission_interfaces__srv__GetLawnmowerPath_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__are_equal(const mission_interfaces__srv__GetLawnmowerPath_Request__Sequence * lhs, const mission_interfaces__srv__GetLawnmowerPath_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!mission_interfaces__srv__GetLawnmowerPath_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__copy(
  const mission_interfaces__srv__GetLawnmowerPath_Request__Sequence * input,
  mission_interfaces__srv__GetLawnmowerPath_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(mission_interfaces__srv__GetLawnmowerPath_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    mission_interfaces__srv__GetLawnmowerPath_Request * data =
      (mission_interfaces__srv__GetLawnmowerPath_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!mission_interfaces__srv__GetLawnmowerPath_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          mission_interfaces__srv__GetLawnmowerPath_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!mission_interfaces__srv__GetLawnmowerPath_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `waypoint_x`
// Member `waypoint_y`
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
mission_interfaces__srv__GetLawnmowerPath_Response__init(mission_interfaces__srv__GetLawnmowerPath_Response * msg)
{
  if (!msg) {
    return false;
  }
  // waypoint_x
  if (!rosidl_runtime_c__double__Sequence__init(&msg->waypoint_x, 0)) {
    mission_interfaces__srv__GetLawnmowerPath_Response__fini(msg);
    return false;
  }
  // waypoint_y
  if (!rosidl_runtime_c__double__Sequence__init(&msg->waypoint_y, 0)) {
    mission_interfaces__srv__GetLawnmowerPath_Response__fini(msg);
    return false;
  }
  return true;
}

void
mission_interfaces__srv__GetLawnmowerPath_Response__fini(mission_interfaces__srv__GetLawnmowerPath_Response * msg)
{
  if (!msg) {
    return;
  }
  // waypoint_x
  rosidl_runtime_c__double__Sequence__fini(&msg->waypoint_x);
  // waypoint_y
  rosidl_runtime_c__double__Sequence__fini(&msg->waypoint_y);
}

bool
mission_interfaces__srv__GetLawnmowerPath_Response__are_equal(const mission_interfaces__srv__GetLawnmowerPath_Response * lhs, const mission_interfaces__srv__GetLawnmowerPath_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // waypoint_x
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->waypoint_x), &(rhs->waypoint_x)))
  {
    return false;
  }
  // waypoint_y
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->waypoint_y), &(rhs->waypoint_y)))
  {
    return false;
  }
  return true;
}

bool
mission_interfaces__srv__GetLawnmowerPath_Response__copy(
  const mission_interfaces__srv__GetLawnmowerPath_Response * input,
  mission_interfaces__srv__GetLawnmowerPath_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // waypoint_x
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->waypoint_x), &(output->waypoint_x)))
  {
    return false;
  }
  // waypoint_y
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->waypoint_y), &(output->waypoint_y)))
  {
    return false;
  }
  return true;
}

mission_interfaces__srv__GetLawnmowerPath_Response *
mission_interfaces__srv__GetLawnmowerPath_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mission_interfaces__srv__GetLawnmowerPath_Response * msg = (mission_interfaces__srv__GetLawnmowerPath_Response *)allocator.allocate(sizeof(mission_interfaces__srv__GetLawnmowerPath_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(mission_interfaces__srv__GetLawnmowerPath_Response));
  bool success = mission_interfaces__srv__GetLawnmowerPath_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
mission_interfaces__srv__GetLawnmowerPath_Response__destroy(mission_interfaces__srv__GetLawnmowerPath_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    mission_interfaces__srv__GetLawnmowerPath_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__init(mission_interfaces__srv__GetLawnmowerPath_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mission_interfaces__srv__GetLawnmowerPath_Response * data = NULL;

  if (size) {
    data = (mission_interfaces__srv__GetLawnmowerPath_Response *)allocator.zero_allocate(size, sizeof(mission_interfaces__srv__GetLawnmowerPath_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = mission_interfaces__srv__GetLawnmowerPath_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        mission_interfaces__srv__GetLawnmowerPath_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__fini(mission_interfaces__srv__GetLawnmowerPath_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      mission_interfaces__srv__GetLawnmowerPath_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

mission_interfaces__srv__GetLawnmowerPath_Response__Sequence *
mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mission_interfaces__srv__GetLawnmowerPath_Response__Sequence * array = (mission_interfaces__srv__GetLawnmowerPath_Response__Sequence *)allocator.allocate(sizeof(mission_interfaces__srv__GetLawnmowerPath_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__destroy(mission_interfaces__srv__GetLawnmowerPath_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__are_equal(const mission_interfaces__srv__GetLawnmowerPath_Response__Sequence * lhs, const mission_interfaces__srv__GetLawnmowerPath_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!mission_interfaces__srv__GetLawnmowerPath_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__copy(
  const mission_interfaces__srv__GetLawnmowerPath_Response__Sequence * input,
  mission_interfaces__srv__GetLawnmowerPath_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(mission_interfaces__srv__GetLawnmowerPath_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    mission_interfaces__srv__GetLawnmowerPath_Response * data =
      (mission_interfaces__srv__GetLawnmowerPath_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!mission_interfaces__srv__GetLawnmowerPath_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          mission_interfaces__srv__GetLawnmowerPath_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!mission_interfaces__srv__GetLawnmowerPath_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "mission_interfaces/srv/detail/get_lawnmower_path__functions.h"

bool
mission_interfaces__srv__GetLawnmowerPath_Event__init(mission_interfaces__srv__GetLawnmowerPath_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    mission_interfaces__srv__GetLawnmowerPath_Event__fini(msg);
    return false;
  }
  // request
  if (!mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__init(&msg->request, 0)) {
    mission_interfaces__srv__GetLawnmowerPath_Event__fini(msg);
    return false;
  }
  // response
  if (!mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__init(&msg->response, 0)) {
    mission_interfaces__srv__GetLawnmowerPath_Event__fini(msg);
    return false;
  }
  return true;
}

void
mission_interfaces__srv__GetLawnmowerPath_Event__fini(mission_interfaces__srv__GetLawnmowerPath_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__fini(&msg->request);
  // response
  mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__fini(&msg->response);
}

bool
mission_interfaces__srv__GetLawnmowerPath_Event__are_equal(const mission_interfaces__srv__GetLawnmowerPath_Event * lhs, const mission_interfaces__srv__GetLawnmowerPath_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
mission_interfaces__srv__GetLawnmowerPath_Event__copy(
  const mission_interfaces__srv__GetLawnmowerPath_Event * input,
  mission_interfaces__srv__GetLawnmowerPath_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!mission_interfaces__srv__GetLawnmowerPath_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!mission_interfaces__srv__GetLawnmowerPath_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

mission_interfaces__srv__GetLawnmowerPath_Event *
mission_interfaces__srv__GetLawnmowerPath_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mission_interfaces__srv__GetLawnmowerPath_Event * msg = (mission_interfaces__srv__GetLawnmowerPath_Event *)allocator.allocate(sizeof(mission_interfaces__srv__GetLawnmowerPath_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(mission_interfaces__srv__GetLawnmowerPath_Event));
  bool success = mission_interfaces__srv__GetLawnmowerPath_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
mission_interfaces__srv__GetLawnmowerPath_Event__destroy(mission_interfaces__srv__GetLawnmowerPath_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    mission_interfaces__srv__GetLawnmowerPath_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
mission_interfaces__srv__GetLawnmowerPath_Event__Sequence__init(mission_interfaces__srv__GetLawnmowerPath_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mission_interfaces__srv__GetLawnmowerPath_Event * data = NULL;

  if (size) {
    data = (mission_interfaces__srv__GetLawnmowerPath_Event *)allocator.zero_allocate(size, sizeof(mission_interfaces__srv__GetLawnmowerPath_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = mission_interfaces__srv__GetLawnmowerPath_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        mission_interfaces__srv__GetLawnmowerPath_Event__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
mission_interfaces__srv__GetLawnmowerPath_Event__Sequence__fini(mission_interfaces__srv__GetLawnmowerPath_Event__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      mission_interfaces__srv__GetLawnmowerPath_Event__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

mission_interfaces__srv__GetLawnmowerPath_Event__Sequence *
mission_interfaces__srv__GetLawnmowerPath_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  mission_interfaces__srv__GetLawnmowerPath_Event__Sequence * array = (mission_interfaces__srv__GetLawnmowerPath_Event__Sequence *)allocator.allocate(sizeof(mission_interfaces__srv__GetLawnmowerPath_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = mission_interfaces__srv__GetLawnmowerPath_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
mission_interfaces__srv__GetLawnmowerPath_Event__Sequence__destroy(mission_interfaces__srv__GetLawnmowerPath_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    mission_interfaces__srv__GetLawnmowerPath_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
mission_interfaces__srv__GetLawnmowerPath_Event__Sequence__are_equal(const mission_interfaces__srv__GetLawnmowerPath_Event__Sequence * lhs, const mission_interfaces__srv__GetLawnmowerPath_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!mission_interfaces__srv__GetLawnmowerPath_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
mission_interfaces__srv__GetLawnmowerPath_Event__Sequence__copy(
  const mission_interfaces__srv__GetLawnmowerPath_Event__Sequence * input,
  mission_interfaces__srv__GetLawnmowerPath_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(mission_interfaces__srv__GetLawnmowerPath_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    mission_interfaces__srv__GetLawnmowerPath_Event * data =
      (mission_interfaces__srv__GetLawnmowerPath_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!mission_interfaces__srv__GetLawnmowerPath_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          mission_interfaces__srv__GetLawnmowerPath_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!mission_interfaces__srv__GetLawnmowerPath_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
