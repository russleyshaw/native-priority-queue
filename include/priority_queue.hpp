#ifndef _PRIORITY_QUEUE_HPP_INCLUDED
#define _PRIORITY_QUEUE_HPP_INCLUDED

#include <node_api.h>
#include <queue>

class Priority_queue
{
public:
  static napi_value Init(napi_env env, napi_value exports);
  static void Destroy(napi_env env, void* native_object, void* finalize_hint);

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

  std::priority_queue<napi_value> _pq;
};

#endif