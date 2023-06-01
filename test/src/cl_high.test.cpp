#include <iostream>
#include <string>
#include <cassert>

#include "cl_high.hpp"

SCENARIO_START

DESCRIBE("cl_high", {
	IT("should get all platforms", {
		auto platforms = cl_high::Devices::platforms();
		EXPECT(platforms.size()).NOT().toBe(0);
		for(auto& it : platforms) {
			INFO_PRINT() << it.get_info().name;
		}
	});
	IT("should get all GPU devices", {
		auto devices = cl_high::Devices::gpu_devices();
		EXPECT(devices.size()).NOT().toBe(0);
		for(auto& it : devices) {
			INFO_PRINT() << it.get_info().name;
		}
	});
	IT("should get all CPU devices", {
		auto platform = cl_high::Devices::platforms()[1];
		auto devices = cl_high::Devices::cpu_devices(platform);
		EXPECT(devices.size()).NOT().toBe(0);
		for(auto& it : devices) {
			INFO_PRINT() << it.get_info().name;
		}
	});
	IT("should get all devices", {
		auto platform = cl_high::Devices::platforms()[1];
		auto devices = cl_high::Devices::all_devices(platform);
		EXPECT(devices.size()).NOT().toBe(0);
		for(auto& it : devices) {
			INFO_PRINT() << it.get_info().name;
		}
	});
	
	DESCRIBE("Given compute station", {
		cl_high::ComputeStation compute;
		
		BEFORE_EACH({
			auto device = cl_high::Devices::gpu_devices()[0];
			compute = cl_high::ComputeStation::from_device(device);
		});
		
		IT("should succeed", {
			TEST_SUCCEED();
		});
		
		IT("should create a queue", {
			cl_high::Queue queue = compute.create_queue();
			TEST_SUCCEED();
		});
		
		IT("should create a buffer", {
			cl_high::Buffer b1 = compute.create_buffer(cl_high::AccessType::READ, 1000 * sizeof(float));
			cl_high::Buffer b2 = compute.create_buffer<float>(cl_high::AccessType::READ, 1000);
			cl_high::Buffer b3 = cl_high::Buffer::from(compute.get_context()).allocate(cl_high::AccessType::READ, sizeof(float) * 1000);
			cl_high::Buffer b4 = cl_high::Buffer::from(compute.get_context()).allocate<float>(cl_high::AccessType::READ, 1000);
			cl_high::Buffer empty_buf;
			
			EXPECT(empty_buf.empty()).toBe(true);
			EXPECT(empty_buf.size()).toBe(0);
			EXPECT(b1.size()).toBe(b2.size());
			EXPECT(b2.size()).toBe(b3.size());
			EXPECT(b3.size()).toBe(b4.size());
			EXPECT(b1.empty()).toBe(false);
		});
		
		IT("should build a program", {
			cl_high::Program p1 = compute.build({get_fn_kernel_source()});
			cl_high::Program p2 = cl_high::Program::from(compute.get_context()).build(get_fn_kernel_source());
			TEST_SUCCEED();
		});
		
		IT("should run the kernel", {
			cl_high::Queue q = compute.create_queue();
			cl_high::Program p = compute.build(get_fn_kernel_source());
			const size_t SIZE = 1024;
			cl_high::Buffer b1 = compute.create_buffer<float>(cl_high::AccessType::READ, SIZE);
			cl_high::Buffer b2 = compute.create_buffer<float>(cl_high::AccessType::READ, SIZE);
			cl_high::Buffer b3 = compute.create_buffer<float>(cl_high::AccessType::WRITE, SIZE);
			std::vector<float> v1(SIZE), v2(SIZE), v3(SIZE);
			for(size_t i=0;i<SIZE;i++){
				v1[i] = i;
				v2[i] = SIZE-i;
				v3[i] = 0;
			}
			
			cl_high::Event ea = b1.write(v1.data(), SIZE).on_queue(q).run();
			cl_high::Event eb = b2.write(v2.data(), SIZE).on_queue(q).run();
			cl_high::Event er = p.prepare_kernel("fn_kernel", (float)2.0, b1, b2, b3).with_parameters(SIZE, 64).on_queue(q).wait_for({ea, eb}).run();
			cl_high::Event ec = b3.read(v3.data(), SIZE).on_queue(q).wait_for({er}).run();
			
			ec.await();
			
			for(size_t i=0;i<SIZE;i++) {
				EXPECT(v3[i]).toBe(2048);
			}
		});
	});
});

SCENARIO_END

/*

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

*/