#include <iostream>
#include <cassert>
#include <chrono>

#include "cl_helper.hpp"

std::string source = 
"__kernel                                   \n"
"void fn_kernel(float alpha,     \n"
"                  __global float4 *A,       \n"
"                  __global float4 *B,       \n"
"                  __global float4 *C)       \n"
"{                                          \n"
"    //Get the index of the work-item       \n"
"    int index = get_global_id(0);          \n"
"              \n"
"    C[index] = alpha * (A[index] + B[index]); \n"
"                                          \n"
"}                                          \n";

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
	const size_t VECTOR_SIZE = 1024 * 1024 * 100;
	std::vector<float> A(VECTOR_SIZE), B(VECTOR_SIZE), C(VECTOR_SIZE);
	for(size_t i = 0; i < VECTOR_SIZE; i++)
	{
		A[i] = i;
		B[i] = VECTOR_SIZE - i;
		C[i] = 0;
	}

	cl_mem A_clmem = CLHelper::create_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * VECTOR_SIZE);
	cl_mem B_clmem = CLHelper::create_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * VECTOR_SIZE);
	cl_mem C_clmem = CLHelper::create_buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * VECTOR_SIZE);

	///////

	cl_event ea = CLHelper::write(queue, A_clmem, 0, VECTOR_SIZE * sizeof(float), A.data());
	cl_event eb = CLHelper::write(queue, B_clmem, 0, VECTOR_SIZE * sizeof(float), B.data());

	///////

	cl_program program = CLHelper::create_program(context, std::vector<std::string>(1, source));
	std::cout << "CL_PROGRAM: " << program << std::endl;

	///////

	CLHelper::build_program(program, device_ids);

	///////

	cl_kernel kernel = CLHelper::create_kernel(program, "fn_kernel");
	std::cout << "CL_KERNEL: " << kernel << std::endl;

	///////

	std::cout << "_____________________" << std::endl;
	std::cout << "CL_INVALID_PROGRAM_EXECUTABLE : " << CL_INVALID_PROGRAM_EXECUTABLE << std::endl;
	std::cout << "CL_INVALID_COMMAND_QUEUE  : " << CL_INVALID_COMMAND_QUEUE  << std::endl;
	std::cout << "CL_INVALID_KERNEL  : " << CL_INVALID_KERNEL  << std::endl;
	std::cout << "CL_INVALID_CONTEXT  : " << CL_INVALID_CONTEXT  << std::endl;
	std::cout << "CL_INVALID_KERNEL_ARGS  : " << CL_INVALID_KERNEL_ARGS  << std::endl;
	std::cout << "CL_INVALID_WORK_DIMENSION  : " << CL_INVALID_WORK_DIMENSION  << std::endl;
	std::cout << "CL_INVALID_WORK_GROUP_SIZE  : " << CL_INVALID_WORK_GROUP_SIZE  << std::endl;
	std::cout << "CL_INVALID_WORK_ITEM_SIZE   : " << CL_INVALID_WORK_ITEM_SIZE   << std::endl;
	std::cout << "CL_INVALID_GLOBAL_OFFSET   : " << CL_INVALID_GLOBAL_OFFSET   << std::endl;
	std::cout << "CL_OUT_OF_RESOURCES  : " << CL_OUT_OF_RESOURCES  << std::endl;
	std::cout << "CL_MEM_OBJECT_ALLOCATION_FAILURE   : " << CL_MEM_OBJECT_ALLOCATION_FAILURE   << std::endl;
	std::cout << "CL_INVALID_EVENT_WAIT_LIST   : " << CL_INVALID_EVENT_WAIT_LIST   << std::endl;
	std::cout << "CL_OUT_OF_HOST_MEMORY   : " << CL_OUT_OF_HOST_MEMORY   << std::endl;
	std::cout << "_____________________" << std::endl;

	///////

	float alpha = 2.0;
	CLHelper::set_kernel_arg(kernel, 0, sizeof(float), &alpha);
	CLHelper::set_kernel_arg(kernel, 1, sizeof(cl_mem), &A_clmem);
	CLHelper::set_kernel_arg(kernel, 2, sizeof(cl_mem), &B_clmem);
	CLHelper::set_kernel_arg(kernel, 3, sizeof(cl_mem), &C_clmem);

	///////

	size_t local_size = 64;
	
	auto t1 = std::chrono::system_clock::now();
	cl_event er = CLHelper::run_kernel(queue, kernel, {0}, {VECTOR_SIZE/4}, {local_size}, {ea, eb});
	CLHelper::await_events({er});
	auto t2 = std::chrono::system_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << "ms" << std::endl;

	///////

	cl_event ac = CLHelper::read(queue, C_clmem, 0, VECTOR_SIZE * sizeof(float), C.data());

	///////

	CLHelper::await_events({ac});

	///////

	CLHelper::flush(queue);
	CLHelper::finish(queue);

	///////

	CLHelper::release_kernel(kernel);
	CLHelper::release_program(program);
	CLHelper::release_context(context);
	CLHelper::release_command_queue(queue);
	CLHelper::release_mem(A_clmem);
	CLHelper::release_mem(B_clmem);
	CLHelper::release_mem(C_clmem);
	CLHelper::release_event(ea);
	CLHelper::release_event(eb);
	CLHelper::release_event(er);

	///////

	for(size_t i=0;i<VECTOR_SIZE;i++) {
		assert(C[i] == 2 * VECTOR_SIZE);
	}

	std::cout << "FINISHED" << std::endl;
}