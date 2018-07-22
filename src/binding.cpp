#define NAPI_VERSION 3
#include <node_api.h>

#include "priority_queue.hpp"

NAPI_MODULE_INIT()
{
  Priority_queue::Init(env, exports);
  return exports;
}