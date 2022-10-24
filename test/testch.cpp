#include <iostream>
#include <string>
#include <cassert>

#include "cl_high.hpp"

std::string source = 
"__kernel                                   \n"
"void saxpy_kernel(float alpha,     \n"
"                  __global float *A,       \n"
"                  __global float *B,       \n"
"                  __global float *C)       \n"
"{                                          \n"
"    //Get the index of the work-item       \n"
"    int index = get_global_id(0);          \n"
"              \n"
"    C[index] = alpha * (A[index] + B[index]); \n"
"                                          \n"
"}                                          \n";

int main() {
	std::cout << "TEST STARTS" << std::endl;
	
	cl_high::ComputeStation compute = cl_high::ComputeStation::from_device(cl_high::Devices::gpu_devices()[0]);
	cl_high::Queue queue = compute.create_queue();
	
	const size_t VECTOR_SIZE = 1000000;
	std::vector<float> A(VECTOR_SIZE), B(VECTOR_SIZE), C(VECTOR_SIZE);
	for(size_t i = 0; i < VECTOR_SIZE; i++) {
		A[i] = i;
		B[i] = VECTOR_SIZE - i;
		C[i] = 0;
	}
	
	cl_high::Buffer b_a = compute.create_buffer(cl_high::AccessType::READ, sizeof(float) * VECTOR_SIZE);
	cl_high::Buffer b_b = compute.create_buffer(cl_high::AccessType::READ, sizeof(float) * VECTOR_SIZE);
	cl_high::Buffer b_c = compute.create_buffer(cl_high::AccessType::WRITE, sizeof(float) * VECTOR_SIZE);
	
	cl_high::Event e_a = b_a.write(A.data(), VECTOR_SIZE).on_queue(queue).run();
	cl_high::Event e_b = b_b.write(B.data(), VECTOR_SIZE).on_queue(queue).run();
	
	cl_high::Program program = compute.build({source});
	cl_high::Kernel kernel = program.create_kernel("saxpy_kernel");
	
	cl_high::Event er = kernel.prepare((float)2.0, b_a, b_b, b_c).on_queue(queue).with_parameters(VECTOR_SIZE, 64).wait_for({e_a, e_b}).run();
	
	cl_high::Event e_c = b_c.read(C.data(), VECTOR_SIZE).on_queue(queue).wait_for({er}).run();
	
	e_c.await();
	queue.flush();
	
	for(size_t i=0;i<VECTOR_SIZE;i++) {
		assert(C[i] == 2000000);
	}
	
	std::cout << "TEST FINISHED" << std::endl;
	
	return 0;
}