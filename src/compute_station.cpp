#include "compute_station.hpp"

cl_high::ComputeStation::ComputeStation(Device device): device_id(device.get()), context(CLHelper::create_context({device_id})) {}

cl_high::ComputeStation::ComputeStation(const ComputeStation& instance): device_id(instance.device_id), context(instance.context) {}

cl_high::ComputeStation& cl_high::ComputeStation::operator=(const ComputeStation& instance) {
	device_id = instance.device_id;
	context = instance.context;
	return *this;
}

cl_high::ComputeStation::~ComputeStation() {
	CLHelper::release_context(context);
}

cl_high::ComputeStation cl_high::ComputeStation::from_device(Device device) {
	return ComputeStation(device);
}

cl_high::Context cl_high::ComputeStation::get_context() {
	return Context(context, device_id);
}

cl_high::Queue cl_high::ComputeStation::create_queue() {
	return Queue(CLHelper::create_queue(context, device_id));
}

cl_high::Program cl_high::ComputeStation::build(std::vector<std::string> sources, std::string options) {
	return Program::from(get_context()).build(sources, options);
}

cl_high::Buffer cl_high::ComputeStation::create_buffer(AccessType type, size_t size) {
	return Buffer::from(get_context()).allocate(type, size);
}