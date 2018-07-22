#ifndef _NAPI_UTILITY_HPP_INCLUDED
#define _NAPI_UTILITY_HPP_INCLUDED

#include <cassert>
#include <iostream>
#include <string>
#include <node_api.h>

#ifndef NDEBUG 
#define LOG_DEBUG(msg) std::cerr << "debug - " << msg << std::endl;
#elif
#define LOG_DEBUG(msg)
#endif

#define DECLARE_NAPI_METHOD(name, func) { name, 0, func, 0, 0, 0, napi_default, 0 }
#define CHECK_OK(status) if(status != napi_ok) { LOG_DEBUG("napi_status = " << status); } assert(status == napi_ok)

napi_value create_undefined(napi_env env) {
	napi_status status;
	napi_value value;
	status = napi_get_undefined(env, &value);
	CHECK_OK(status);
	return value;
}

template<typename T>
class Callback_info {
public: 
	napi_env env;
	napi_callback_info info;
	std::vector<napi_value> args;
	napi_value jsthis;
	T* cthis;

	Callback_info(napi_env env, napi_callback_info info) {
		this->env = env;
		this->info = info;

		napi_status status;

		std::size_t argc = NAPI_AUTO_LENGTH;
		status = napi_get_cb_info(env, info, &argc, nullptr, nullptr, nullptr); // Get argc
		CHECK_OK(status);

		args.resize(argc);
		status = napi_get_cb_info(env, info, &argc, args.data(), &jsthis, nullptr); // Get argc
		CHECK_OK(status);

		status = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&cthis));
		CHECK_OK(status);
	}


};

#endif