#include "context.hpp"

cl_high::Context::Context(): context(nullptr), device_id(nullptr) {}

cl_high::Context::~Context() {}

cl_high::Context::Context(cl_context context, cl_device_id device_id) : context(context), device_id(device_id) {}

cl_context cl_high::Context::get() const {
	return context;
}

cl_device_id cl_high::Context::device() const {
	return device_id;
}
