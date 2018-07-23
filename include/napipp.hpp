#ifndef _NAPIPP_HPP_INCLUDED_
#define _NAPIPP_HPP_INCLUDED_

#include <cassert>
#include <iostream>
#include <string>

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

napi_value get_undefined(napi_env env)
{
	napi_value value;
	auto status = napi_get_undefined(env, &value);
	CHECK_OK(status);
	return value;
}

napi_value get_null(napi_env env)
{
	napi_value value;
	auto status = napi_get_undefined(env, &value);
	CHECK_OK(status);
	return value;
}

napi_value get_boolean(napi_env env, bool b)
{
	napi_value value;
	auto status = napi_get_boolean(env, b, &value);
	CHECK_OK(status);
	return value;
}

napi_ref create_reference(napi_env env, napi_value value, uint32_t initial_refcount = 0)
{
	napi_ref ref;
	auto status = napi_create_reference(env, value, initial_refcount, &ref);
	CHECK_OK(status);
	return ref;
}

napi_value get_reference_value(napi_env env, napi_ref ref)
{
	napi_value value;
	auto status = napi_get_reference_value(env, ref, &value);
	CHECK_OK(status);
	return value;
}

napi_valuetype typeof(napi_env env, napi_value value)
{
	napi_valuetype type;
	auto status = napi_typeof(env, value, &type);
	CHECK_OK(status);
	return type;
}

napi_value create_double(napi_env env, double value)
{
	napi_value result;
	auto status = napi_create_double(env, value, &result);
	CHECK_OK(status);
	return result;
}

napi_value create_string(napi_env env, std::string str)
{
	napi_value result;
	auto status = napi_create_string_utf8(env, str.c_str(), NAPI_AUTO_LENGTH, &result);
	CHECK_OK(status);
	return result;
}

void reference_unref(napi_env env, napi_ref ref)
{
	auto status = napi_reference_unref(env, ref, nullptr);
	CHECK_OK(status);
}

napi_value call_function(napi_env env, napi_value func, std::vector<napi_value> args)
{
	napi_value result;
	auto status = napi_call_function(env, get_undefined(env), func, args.size(), args.data(), &result);
	CHECK_OK(status);
	return result;
}

double get_value_double(napi_env env, napi_value value)
{
	double result;
	auto status = napi_get_value_double(env, value, &result);
	CHECK_OK(status);
	return result;
}

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

#define NAPIPP_CHECK_VALUE_TYPE(env, value, type) assert(napipp::typeof(env, value) == type)

} // namespace napipp
#endif