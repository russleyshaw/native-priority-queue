
#include <vector>
#include <cassert>

#include "priority_queue.hpp";
#include "napi_utility.hpp";

napi_ref Priority_queue::constructor;

Priority_queue::Priority_queue() {}
Priority_queue::~Priority_queue() {
	napi_delete_reference(_env, _wrapper);
}

void Priority_queue::Destroy(napi_env env, void* native_object, void* finalize_hint) {
	reinterpret_cast<Priority_queue*>(native_object)->~Priority_queue();
}

napi_value Priority_queue::Init(napi_env env, napi_value exports)
{
	napi_status status;

	auto properties = std::vector<napi_property_descriptor>{
		DECLARE_NAPI_METHOD("empty", GetIsEmpty),
		DECLARE_NAPI_METHOD("size", GetSize),
		DECLARE_NAPI_METHOD("push", PushValues),
		DECLARE_NAPI_METHOD("top", GetTop),
		DECLARE_NAPI_METHOD("pop", PopValue)
	};

	napi_value cons;
	status = napi_define_class(env, "PriorityQueue", NAPI_AUTO_LENGTH, New, NULL, properties.size(), properties.data(), &cons);
	CHECK_OK(status);

	status = napi_create_reference(env, cons, 1, &constructor);
	CHECK_OK(status);

	status = napi_set_named_property(env, exports, "PriorityQueue", cons);
	CHECK_OK(status);

    return exports;
}

napi_value Priority_queue::New(napi_env env, napi_callback_info info) {
	napi_status status;

	napi_value target;
	status = napi_get_new_target(env, info, &target);
	CHECK_OK(status);
	auto is_constructor = target != nullptr;
	if (is_constructor) {
		// Invoked as constructor: `new MyObject(...)`;
		napi_value jsthis;
		status = napi_get_cb_info(env, info, 0, nullptr, &jsthis, nullptr);
		CHECK_OK(status);

		auto obj = new Priority_queue();
		obj->_env = env;
		status = napi_wrap(env, jsthis, reinterpret_cast<void*>(obj), Priority_queue::Destroy, nullptr, &obj->_wrapper);
		CHECK_OK(status);

		return jsthis;
	}
	else {
		// Invoked as plain function `MyObject(...)`, turn into construct call.
		status = napi_get_cb_info(env, info, 0, nullptr, nullptr, nullptr);
		CHECK_OK(status);

		napi_value cons;
		status = napi_get_reference_value(env, constructor, &cons);
		CHECK_OK(status);

		napi_value instance;
		status = napi_new_instance(env, cons, 0, nullptr, &instance);
		CHECK_OK(status);

		return instance;
	}
}

napi_value Priority_queue::GetIsEmpty(napi_env env, napi_callback_info cbinfo) {
	napi_status status;
	Callback_info<Priority_queue> info(env, cbinfo);
	auto obj = info.cthis;

	napi_value val;
	status = napi_get_boolean(env, obj->_pq.empty(), &val);
	CHECK_OK(status);

	return val;
}

napi_value Priority_queue::GetSize(napi_env env, napi_callback_info cbinfo) {
	napi_status status;
	Callback_info<Priority_queue> info(env, cbinfo);
	auto obj = info.cthis;

	napi_value val;
	status = napi_create_uint32(env, obj->_pq.size(), &val);
	CHECK_OK(status);

	return val;
}

napi_value Priority_queue::PushValues(napi_env env, napi_callback_info cbinfo) {
	napi_status status;

	Callback_info<Priority_queue> info(env, cbinfo);
	auto obj = info.cthis;

	for (auto arg: info.args) {
		obj->_pq.push(arg);
	}

	return create_undefined(env);
}

napi_value Priority_queue::GetTop(napi_env env, napi_callback_info cbinfo) {
	napi_status status;

	Callback_info<Priority_queue> info(env, cbinfo);
	auto obj = info.cthis;

	if (obj->_pq.empty()) {
		return create_undefined(env);
	}

	auto value = obj->_pq.top();
	return value;
}

napi_value Priority_queue::PopValue(napi_env env, napi_callback_info cbinfo) {
	napi_status status;

	Callback_info<Priority_queue> info(env, cbinfo);

	auto obj = info.cthis;

	if (!obj->_pq.empty()) {
		obj->_pq.pop();
	}

	napi_value result;
	status = napi_get_undefined(env, &result);
	CHECK_OK(status);

	return result;
}
