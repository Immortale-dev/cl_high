#include "cl_helper.hpp"

std::vector<cl_platform_id> CLHelper::get_platform_ids(){
	cl_uint num_platforms;
	cl_int clStatus = clGetPlatformIDs(0, NULL, &num_platforms);
	confirm_status(clStatus);
	
	std::vector<cl_platform_id> platforms(num_platforms);
	clStatus = clGetPlatformIDs(num_platforms, platforms.data(), NULL);
	confirm_status(clStatus);
	
	return platforms;
}

std::vector<cl_device_id> CLHelper::get_device_ids(cl_platform_id platform_id, cl_device_type device_type) {
	cl_uint num_devices;
	cl_int clStatus = clGetDeviceIDs( platform_id, device_type, 0, NULL, &num_devices);
	confirm_status(clStatus);
	
	std::vector<cl_device_id> devices(num_devices);
	clStatus = clGetDeviceIDs( platform_id, device_type, num_devices, devices.data(), NULL);
	confirm_status(clStatus);
	
	return devices;
}

cl_command_queue CLHelper::create_queue(cl_context context, cl_device_id device_id) {
	cl_int clStatus;
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &clStatus);
	confirm_status(clStatus);
	
	return command_queue;
}

cl_mem CLHelper::create_buffer(cl_context context, cl_mem_flags flags, size_t size) {
	cl_int clStatus;
	cl_mem mem = clCreateBuffer(context, flags, size, NULL, &clStatus);
	confirm_status(clStatus);
	
	return mem;
}

cl_event CLHelper::write(cl_command_queue queue, cl_mem buffer, size_t offset, size_t size, void *ptr, std::vector<cl_event> events) {
	cl_event event;
	cl_int clStatus = clEnqueueWriteBuffer(queue, buffer, CL_FALSE, offset, size, ptr, events.size(), events.data(), &event);
	confirm_status(clStatus);
	
	return event;
}

cl_event CLHelper::read(cl_command_queue queue, cl_mem buffer, size_t offset, size_t size, void *ptr, std::vector<cl_event> events) {
	cl_event event;
	cl_int clStatus = clEnqueueReadBuffer(queue, buffer, CL_FALSE, offset, size, ptr, events.size(), events.data(), &event);
	confirm_status(clStatus);
	
	return event;
}

cl_program CLHelper::create_program(cl_context context, std::vector<std::string> sources) {
	cl_int clStatus;
	std::vector<size_t> lengths(sources.size());
	std::vector<const char*> sources_ptrs(sources.size());
	for(size_t i=0;i<sources.size();i++){
		lengths[i] = sources[i].size();
		sources_ptrs[i] = sources[i].data();
	}
	cl_program program = clCreateProgramWithSource(context, (cl_uint)sources.size(),(const char **)sources_ptrs.data(), lengths.data(), &clStatus);
	confirm_status(clStatus);
	
	return program;
}

void CLHelper::build_program(cl_program program, std::vector<cl_device_id> devices, std::string options) {
	char* options_term = to_null_terminated_char_ptr(options);
	cl_int clStatus = clBuildProgram(program, devices.size(), devices.data(), options_term, NULL, NULL);
	delete options_term;
	confirm_status(clStatus);
}

cl_kernel CLHelper::create_kernel(cl_program program, std::string kernel_name) {
	cl_int clStatus;
	char* kernel_name_term = to_null_terminated_char_ptr(kernel_name);
	cl_kernel kernel = clCreateKernel(program, kernel_name_term, &clStatus);
	confirm_status(clStatus);
	
	return kernel;
}

void CLHelper::set_kernel_arg(cl_kernel kernel, cl_uint arg_index, size_t arg_size, void *arg_value) {
	cl_int clStatus = clSetKernelArg(kernel, arg_index, arg_size, arg_value);
	confirm_status(clStatus);
}

cl_event CLHelper::run_kernel(cl_command_queue queue, cl_kernel kernel, cl_uint work_dim, const size_t offset, const size_t size, const size_t local_size, std::vector<cl_event> events) {
	cl_event event;
	cl_int clStatus;
	clStatus = clEnqueueNDRangeKernel(queue, kernel, work_dim, &offset, &size, &local_size, events.size(), events.data(), &event);
	confirm_status(clStatus);
	
	return event;
}

void CLHelper::await_events(std::vector<cl_event> events) {
	cl_int clStatus = clWaitForEvents(events.size(), events.data());
	confirm_status(clStatus);
}

void CLHelper::flush(cl_command_queue queue) {
	cl_int clStatus = clFlush(queue);
	confirm_status(clStatus);
}

void CLHelper::finish(cl_command_queue queue) {
	cl_int clStatus = clFinish(queue);
	confirm_status(clStatus);
}

void CLHelper::release_kernel(cl_kernel kernel) {
	cl_int clStatus = clReleaseKernel(kernel);
	confirm_status(clStatus);
}

void CLHelper::release_program(cl_program program) {
	cl_int clStatus = clReleaseProgram(program);
	confirm_status(clStatus);
}

void CLHelper::release_mem(cl_mem mem) {
	cl_int clStatus = clReleaseMemObject(mem);
	confirm_status(clStatus);
}

void CLHelper::release_event(cl_event event) {
	cl_int clStatus = clReleaseEvent(event);
	confirm_status(clStatus);
}

void CLHelper::release_command_queue(cl_command_queue queue) {
	cl_int clStatus = clReleaseCommandQueue(queue);
	confirm_status(clStatus);
}

void CLHelper::release_context(cl_context context) {
	cl_int clStatus = clReleaseContext(context);
	confirm_status(clStatus);
}

void CLHelper::retain_kernel(cl_kernel kernel) {
	cl_int clStatus = clRetainKernel(kernel);
	confirm_status(clStatus);
}

void CLHelper::retain_program(cl_program program) {
	cl_int clStatus = clRetainProgram(program);
	confirm_status(clStatus);
}

void CLHelper::retain_mem(cl_mem mem) {
	cl_int clStatus = clRetainMemObject(mem);
	confirm_status(clStatus);
}

void CLHelper::retain_event(cl_event event) {
	cl_int clStatus = clRetainEvent(event);
	confirm_status(clStatus);
}

void CLHelper::retain_command_queue(cl_command_queue queue) {
	cl_int clStatus = clRetainCommandQueue(queue);
	confirm_status(clStatus);
}

void CLHelper::retain_context(cl_context context) {
	cl_int clStatus = clRetainContext(context);
	confirm_status(clStatus);
}

CLHelper::PlatformInfo CLHelper::get_platform_info(cl_platform_id platform_id) {
	PlatformInfo platform;
	platform.name = get_platform_info_param(platform_id, CL_PLATFORM_NAME);
	platform.vendor = get_platform_info_param(platform_id, CL_PLATFORM_VENDOR);
	platform.version = get_platform_info_param(platform_id, CL_PLATFORM_VERSION);
	return platform;
}

CLHelper::DeviceInfo CLHelper::get_device_info(cl_device_id device_id) {
	DeviceInfo device;
	device.name = get_device_info_param(device_id, CL_DEVICE_NAME);
	device.vendor = get_device_info_param(device_id, CL_DEVICE_VENDOR);
	device.version = get_device_info_param(device_id, CL_DEVICE_VERSION);
	device.max_work_group_size = *((size_t*)get_device_info_param(device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE).data());
	device.global_mem_size = *((cl_ulong*)get_device_info_param(device_id, CL_DEVICE_GLOBAL_MEM_SIZE).data());
	device.local_mem_size = *((cl_ulong*)get_device_info_param(device_id, CL_DEVICE_LOCAL_MEM_SIZE).data());
	device.max_frequency = *((cl_uint*)get_device_info_param(device_id, CL_DEVICE_MAX_CLOCK_FREQUENCY).data());
	device.max_compute_units = *((cl_uint*)get_device_info_param(device_id, CL_DEVICE_MAX_COMPUTE_UNITS).data());
	return device;
}

cl_context CLHelper::create_context (std::vector<cl_device_id> device_ids) {
	cl_int clStatus;
	cl_context context = clCreateContext( NULL, device_ids.size(), device_ids.data(), NULL, NULL, &clStatus);
	confirm_status(clStatus);
	return context;
}




std::string CLHelper::get_platform_info_param(cl_platform_id platform_id, cl_platform_info param) {
	size_t param_value_size;
	cl_int clStatus = clGetPlatformInfo(platform_id, param, 0, NULL, &param_value_size);
	confirm_status(clStatus);
	
	std::vector<char> value(param_value_size);
	clStatus = clGetPlatformInfo(platform_id, param, param_value_size, value.data(), NULL);
	confirm_status(clStatus);
	
	return std::string(value.begin(), value.end());
}

std::string CLHelper::get_device_info_param(cl_device_id device_id, cl_device_info param) {
	size_t param_value_size;
	cl_int clStatus = clGetDeviceInfo(device_id, param, 0, NULL, &param_value_size);
	confirm_status(clStatus);
	
	std::vector<char> value(param_value_size);
	clStatus = clGetDeviceInfo(device_id, param, param_value_size, value.data(), NULL);
	confirm_status(clStatus);
	
	return std::string(value.begin(), value.end());
}

char* CLHelper::to_null_terminated_char_ptr(std::string str) {
	char* str_term = new char[str.size()+1];
	memcpy(str_term, str.data(), sizeof(char) * str.size());
	str_term[str.size()] = '\0';
	return str_term;
}

