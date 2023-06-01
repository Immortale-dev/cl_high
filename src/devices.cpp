#include "devices.hpp"

cl_high::Device::Device(): id(nullptr), info({}) {}

cl_high::Device::~Device() {}

cl_high::Device::Device(cl_device_id id, CLHelper::DeviceInfo info) : id(id), info(info) {}

cl_device_id cl_high::Device::get() {
	return id;
}

const CLHelper::DeviceInfo& cl_high::Device::get_info() {
	return info;
}

cl_high::Platform::Platform(): id(nullptr), info({}) {}

cl_high::Platform::~Platform() {}

cl_high::Platform::Platform(cl_platform_id id, CLHelper::PlatformInfo info) : id(id), info(info) {}

cl_platform_id cl_high::Platform::get() {
	return id;
}

const CLHelper::PlatformInfo& cl_high::Platform::get_info() {
	return info;
}


std::vector<cl_high::Platform> cl_high::Devices::platforms() {
	std::vector<cl_platform_id> platform_ids = CLHelper::get_platform_ids();
	std::vector<Platform> platforms;
	for (size_t i=0;i<platform_ids.size();i++) {
		platforms.emplace_back(Platform(platform_ids[i], CLHelper::get_platform_info(platform_ids[i])));
	}
	return platforms;
}

std::vector<cl_high::Device> cl_high::Devices::cpu_devices(Platform platform) {
	cl_platform_id platform_id = platform.get();
	if (!platform_id){
		platform_id = get_first_platform_id();
	}
	std::vector<cl_device_id> device_ids = CLHelper::get_device_ids(platform_id, CL_DEVICE_TYPE_CPU);
	std::vector<Device> devices;
	for (size_t i=0;i<device_ids.size();i++) {
		devices.emplace_back(Device(device_ids[i], CLHelper::get_device_info(device_ids[i])));
	}
	return devices;
}

std::vector<cl_high::Device> cl_high::Devices::gpu_devices(Platform platform) {
	cl_platform_id platform_id = platform.get();
	if (!platform_id){
		platform_id = get_first_platform_id();
	}
	std::vector<cl_device_id> device_ids = CLHelper::get_device_ids(platform_id, CL_DEVICE_TYPE_GPU);
	std::vector<Device> devices;
	for (size_t i=0;i<device_ids.size();i++) {
		devices.emplace_back(Device(device_ids[i], CLHelper::get_device_info(device_ids[i])));
	}
	return devices;
}

std::vector<cl_high::Device> cl_high::Devices::all_devices(Platform platform) {
	cl_platform_id platform_id = platform.get();
	if (!platform_id){
		platform_id = get_first_platform_id();
	}
	std::vector<cl_device_id> device_ids = CLHelper::get_device_ids(platform_id, CL_DEVICE_TYPE_ALL);
	std::vector<Device> devices;
	for (size_t i=0;i<device_ids.size();i++) {
		devices.emplace_back(Device(device_ids[i], CLHelper::get_device_info(device_ids[i])));
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
