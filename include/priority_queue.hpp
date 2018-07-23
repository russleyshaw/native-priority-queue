#ifndef _PRIORITY_QUEUE_HPP_INCLUDED_
#define _PRIORITY_QUEUE_HPP_INCLUDED_

#include <node_api.h>
#include <queue>

#include "napipp.hpp"

template <typename T>
struct Prioritized_value
{
  T value;
  double priority;
  friend bool operator<(const Prioritized_value<T> &lhs, const Prioritized_value<T> &rhs)
  {
    return lhs.priority < rhs.priority;
  }
};

class Priority_queue
{
public:
  static napi_value Init(napi_env env, napi_value exports);
  static void Destroy(napi_env env, void *native_object, void *finalize_hint);

private:
  explicit Priority_queue();
  ~Priority_queue();

  static napi_value New(napi_env env, napi_callback_info info);

  static napi_value GetIsEmpty(napi_env env, napi_callback_info info);
  static napi_value GetSize(napi_env env, napi_callback_info info);
  static napi_value PushValues(napi_env env, napi_callback_info info);
  static napi_value GetTop(napi_env env, napi_callback_info info);
  static napi_value PopValue(napi_env env, napi_callback_info info);

  static napi_ref constructor;
  napi_env _env;
  napi_ref _wrapper;
  napi_ref _priority_func;

  using Queue_value = Prioritized_value<napi_ref>;

  std::priority_queue<Queue_value> _pq;
};

#endif