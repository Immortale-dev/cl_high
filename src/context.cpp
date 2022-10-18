#include "context.hpp"

cl_high::Context::Context() {}

cl_high::Context::~Context() {}

cl_high::Context::Context(cl_context context, cl_device_id device_id) : context(context), device_id(device_id) {}

cl_context cl_high::Context::get() {
	return context;
}

cl_device_id cl_high::Context::device() {
	return device_id;
}
