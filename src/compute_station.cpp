#include "compute_station.hpp"

cl_high::ComputeStation::ComputeStation() : device_id(nullptr), context(nullptr) {}

cl_high::ComputeStation::ComputeStation(Device device): device_id(device.get()), context(CLHelper::create_context({device_id})) {}

cl_high::ComputeStation::ComputeStation(const ComputeStation& instance): device_id(instance.device_id), context(instance.context) {
	if (context == nullptr) return;
	CLHelper::retain_context(context);
}

cl_high::ComputeStation& cl_high::ComputeStation::operator=(const ComputeStation& instance) {
	device_id = instance.device_id;
	if (context != nullptr) {
		CLHelper::release_context(context);
	}
	context = instance.context;
	if (context != nullptr) {
		CLHelper::retain_context(context);
	}
	return *this;
}

cl_high::ComputeStation::~ComputeStation() {
	if (context == nullptr) return;
	CLHelper::release_context(context);
}

cl_high::ComputeStation cl_high::ComputeStation::from_device(Device device) {
	return ComputeStation(device);
}

cl_high::Context cl_high::ComputeStation::get_context() {
	return Context(context, device_id);
}

cl_high::Queue cl_high::ComputeStation::create_queue() {
	return Queue::from(get_context()).build();
}

cl_high::Program cl_high::ComputeStation::build(std::vector<std::string> sources, std::string options) {
	return Program::from(get_context()).build(sources, options);
}

cl_high::Program cl_high::ComputeStation::build(std::string source, std::string options) {
	return Program::from(get_context()).build({source}, options);
}

cl_high::Buffer cl_high::ComputeStation::create_buffer(AccessType type, size_t size) {
	return Buffer::from(get_context()).allocate(type, size);
}
