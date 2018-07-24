#ifndef NAPIPP_HPP_INCLUDED
#define NAPIPP_HPP_INCLUDED

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include <node_api.h>

#include "rstd.hpp"

#define DECLARE_NAPI_METHOD(name, func)         \
	{                                           \
		name, 0, func, 0, 0, 0, napi_default, 0 \
	}
#define CHECK_OK(status)                       \
	if (status != napi_ok)                     \
	{                                          \
		RSTD_LOGE("napi_status = " << status); \
	}                                          \
	assert(status == napi_ok)

namespace napipp
{

napi_value get_undefined(napi_env env);
napi_value get_null(napi_env env);
napi_value get_boolean(napi_env env, bool b);
napi_ref create_reference(napi_env env, napi_value value, uint32_t initial_refcount);
napi_value get_reference_value(napi_env env, napi_ref ref);
napi_valuetype typeof_value(napi_env env, napi_value value);
napi_value create_double(napi_env env, double value);
napi_value create_string(napi_env env, std::string str);
void reference_unref(napi_env env, napi_ref ref);
napi_value call_function(napi_env env, napi_value func, std::vector<napi_value> args);
double get_value_double(napi_env env, napi_value value);
napi_value create_object(napi_env env);

void set_property(napi_env env, napi_value object, napi_value key, napi_value value);
void set_property(napi_env env, napi_value object, std::string key, napi_value value);

napi_value get_property(napi_env env, napi_value object, napi_value key);
napi_value get_property(napi_env env, napi_value object, std::string key);

template <typename T>
class Callback_info
{
  public:
	napi_env env;
	napi_callback_info info;
	std::vector<napi_value> args;
	napi_value jsthis;
	T *cthis;

	Callback_info(napi_env env, napi_callback_info info)
	{
		this->env = env;
		this->info = info;

		napi_status status;

		std::size_t argc = NAPI_AUTO_LENGTH;
		status = napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr); // Get argc
		CHECK_OK(status);

		args.resize(argc);
		status = napi_get_cb_info(env, info, &argc, args.data(), &jsthis, nullptr); // Get argc
		CHECK_OK(status);

		status = napi_unwrap(env, jsthis, reinterpret_cast<void **>(&cthis));
		CHECK_OK(status);
	}
};

#define NAPIPP_CHECK_VALUE_TYPE(env, value, type) assert(napipp::typeof_value(env, value) == type)

} // namespace napipp
#endif
