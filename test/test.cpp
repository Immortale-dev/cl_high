#include <iostream>

#include "gpu_helpers.hpp"

int main() {
	auto ids = CLHelper::get_platform_ids();
	
	std::vector<cl_device_id> device_ids;
	
	for(auto it : ids) {
		std::cout << "Platform ID: "<< it << std::endl;
		CLHelper::PlatformInfo platform = CLHelper::get_platform_info(it);
		std::cout << "Name: " << platform.name << std::endl << "Vendor: " << platform.vendor << std::endl << "Version: " << platform.version << std::endl;
		std::cout << std::endl;
		
		device_ids = CLHelper::get_device_ids(it, CL_DEVICE_TYPE_GPU);
		
		std::cout << "Devices: " << std::endl;
		for(auto dit : device_ids) {
			CLHelper::DeviceInfo device = CLHelper::get_device_info(dit);
			std::cout << "Name: " << device.name << std::endl << "Vendor: "<< device.vendor << std::endl << "Version: " << device.version << std::endl
				<< "max_work_group_size: " << device.max_work_group_size << std::endl << "global_mem_size: " << device.global_mem_size << std::endl
				<< "local_mem_size: " << device.local_mem_size << std::endl << "max_frequency: " << device.max_frequency << std::endl
				<< "max_compute_units: " << device.max_compute_units << std::endl;
		}
		
		std::cout << "_____________________" << std::endl;
	}
	
	///////
	
	cl_context context = CLHelper::create_context(device_ids);
	std::cout << "CL_CONTEXT: " << context << std::endl;
	
	///////
	
	cl_command_queue queue = CLHelper::create_queue(context, device_ids[0]);
	std::cout << "CL_COMMAND_QUEUE: " << queue << std::endl;
	
	///////
	
	const size_t VECTOR_SIZE = 1024;
	cl_mem A_clmem = CLHelper::create_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * VECTOR_SIZE);
	cl_mem B_clmem = CLHelper::create_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * VECTOR_SIZE);
	cl_mem C_clmem = CLHelper::create_buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * VECTOR_SIZE);
	
	///////
	
}