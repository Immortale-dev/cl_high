#include "devices.hpp"

cl_high::Device::Device(): id(nullptr), info({}) {}

cl_high::Device::~Device() {}

cl_high::Device::Device(cl_device_id id, CLHelper::DeviceInfo info) : id(id), info(info) {}

cl_device_id cl_high::Device::get() {
	return id;
}

std::vector<cl_high::Device> cl_high::Devices::cpu_devices() {
	std::vector<cl_device_id> device_ids = CLHelper::get_device_ids(get_first_platform_id(), CL_DEVICE_TYPE_CPU);
	std::vector<Device> devices;
	for (size_t i=0;i<device_ids.size();i++) {
		devices.emplace_back(Device(device_ids[i], CLHelper::get_device_info(device_ids[0])));
	}
	return devices;
}

std::vector<cl_high::Device> cl_high::Devices::gpu_devices() {
	std::vector<cl_device_id> device_ids = CLHelper::get_device_ids(get_first_platform_id(), CL_DEVICE_TYPE_GPU);
	std::vector<Device> devices;
	for (size_t i=0;i<device_ids.size();i++) {
		devices.emplace_back(Device(device_ids[i], CLHelper::get_device_info(device_ids[0])));
	}
	return devices;
}

std::vector<cl_high::Device> cl_high::Devices::all_devices() {
	std::vector<cl_device_id> device_ids = CLHelper::get_device_ids(get_first_platform_id(), CL_DEVICE_TYPE_ALL);
	std::vector<Device> devices;
	for (size_t i=0;i<device_ids.size();i++) {
		devices.emplace_back(Device(device_ids[i], CLHelper::get_device_info(device_ids[0])));
	}
	return devices;
}

const cl_platform_id cl_high::Devices::get_first_platform_id() {
	std::vector<cl_platform_id> platforms = CLHelper::get_platform_ids();
	if (!platforms.size()) {
		throw std::range_error("No platforms defined");
	}
	return platforms[0];
}
