#include <string>
#include "cl_helper.hpp"

std::string get_fn_kernel_source() {
	std::string source = 
	"__kernel                                      \n"
	"void fn_kernel(float alpha,                   \n"
	"                  __global float *A,          \n"
	"                  __global float *B,          \n"
	"                  __global float *C)          \n"
	"{                                             \n"
	"    //Get the index of the work-item          \n"
	"    int index = get_global_id(0);             \n"
	"                                              \n"
	"    C[index] = alpha * (A[index] + B[index]); \n"
	"                                              \n"
	"}                                             \n";
	return source;
}

cl_device_id get_first_gpu_device_id() {
	auto p_ids = CLHelper::get_platform_ids();
	auto d_ids = CLHelper::get_device_ids(p_ids[0], CL_DEVICE_TYPE_GPU);
	return d_ids[0];
}
