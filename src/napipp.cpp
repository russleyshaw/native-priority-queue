#include <cassert>
#include <iostream>
#include <string>

#include <node_api.h>

#include "napipp.hpp"
#include "rstd.hpp"
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

napi_valuetype typeof_value(napi_env env, napi_value value)
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

napi_value create_object(napi_env env)
{
	napi_value result;
	auto status = napi_create_object(env, &result);
	CHECK_OK(status);
	return result;
}

void set_property(napi_env env, napi_value object, napi_value key, napi_value value)
{
	auto status = napi_set_property(env, object, key, value);
	CHECK_OK(status);
}

void set_property(napi_env env, napi_value object, std::string key, napi_value value)
{
	auto k = napipp::create_string(env, key);
	auto status = napi_set_property(env, object, k, value);
	CHECK_OK(status);
}


napi_value get_property(napi_env env, napi_value object, napi_value key)
{
	napi_value result;
	auto status = napi_get_property(env, object, key, &result);
	CHECK_OK(status);
	return result;
}
napi_value get_property(napi_env env, napi_value object, std::string key)
{
	napi_value result;
	auto k = napipp::create_string(env, key);
	auto status = napi_get_property(env, object, k, &result);
	CHECK_OK(status);
	return result;
}

} // namespace napipp
