#include <vector>

#include "cl_helper.hpp"

SCENARIO_START

DESCRIBE("CLHelper", {
	DESCRIBE("Platform ids are retrieved", {
		std::vector<cl_platform_id> ids;
		BEFORE_EACH({
			ids = CLHelper::get_platform_ids();
		});
		
		IT("platform ids should be defined", {
			EXPECT(ids.size()).NOT().toBe(0);
		});
		
		IT("should get platform info", {
			CLHelper::PlatformInfo platform = CLHelper::get_platform_info(ids[0]);
			
			EXPECT(platform.name.size()).NOT().toBe(0);
			INFO_PRINT() << "Platform name: " << platform.name;
		});
		
		DESCRIBE("device ids are retrieved", {
			std::vector<cl_device_id> device_ids;
			BEFORE_EACH({
				device_ids = CLHelper::get_device_ids(ids[0], CL_DEVICE_TYPE_GPU);
			});
			
			IT("device ids should be defined", {
				EXPECT(device_ids.size()).NOT().toBe(0);
			});
			
			IT("should get device info", {
				CLHelper::DeviceInfo device = CLHelper::get_device_info(device_ids[0]);
				
				EXPECT(device.name.size()).NOT().toBe(0);
				EXPECT(device.max_work_group_size).NOT().toBe(0);
				EXPECT(device.max_compute_units).NOT().toBe(0);
				EXPECT(device.local_mem_size).NOT().toBe(0);
				INFO_PRINT() << "Device name: " << device.name;
				INFO_PRINT() << "Device work group size: " << device.max_work_group_size;
				INFO_PRINT() << "Device compute units: " << device.max_compute_units;
				INFO_PRINT() << "Device local mem size: " << device.local_mem_size;
			});
		});
	});
	
	DESCRIBE("Given device id", {
		cl_device_id device_id;
		BEFORE_EACH({
			device_id = get_first_gpu_device_id();
		});
		
		DESCRIBE("Create context", {
			cl_context context;
			BEFORE_EACH({
				context = CLHelper::create_context({device_id});
			});
			AFTER_EACH({
				CLHelper::release_context(context);
			});
			
			IT("should succeed", {
				TEST_SUCCEED();
			});
			
			DESCRIBE("Create and build program", {
				cl_program program;
				std::string source = get_fn_kernel_source();
				BEFORE_EACH({
					program = CLHelper::create_program(context, std::vector<std::string>(1, source));
					try {
						CLHelper::build_program(program, {device_id});
					} catch(CLHelper::CLError& e) {
						TEST_FAILED();
						INFO_PRINT() << e.what();
					}
				});
				AFTER_EACH({
					CLHelper::release_program(program);
				});
				
				IT("should succeed", {
					TEST_SUCCEED();
				});
			});
			
			DESCRIBE("Create queue", {
				cl_command_queue queue;
				BEFORE_EACH({
					queue = CLHelper::create_queue(context, device_id);
				});
				AFTER_EACH({
					CLHelper::release_command_queue(queue);
				});
				
				IT("should succeed", {
					TEST_SUCCEED();
				});
				
				DESCRIBE("create a mem of size 1000", {
					cl_mem mem;
					BEFORE_EACH({
						mem = CLHelper::create_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * 1000);
					});
					AFTER_EACH({
						CLHelper::release_mem(mem);
					});
					
					IT("should succeed", {
						TEST_SUCCEED();
					});
					
					IT("should write data to a memory and then read it", {
						float arr[1000];
						for(size_t i=0;i<1000;i++) {
							arr[i] = i;
						}
						cl_event ev = CLHelper::write(queue, mem, 0, 1000 * sizeof(float), arr);
						CLHelper::await_events({ev});
						for(size_t i=0;i<1000;i++) {
							arr[i] = 0;
						}
						ev = CLHelper::read(queue, mem, 0, 1000 * sizeof(float), arr);
						CLHelper::await_events({ev});
						for(size_t i=0;i<1000;i++) {
							EXPECT(arr[i]).toBe(i);
						}
					});
				});
			});
		});
		
		DESCRIBE("Prepare kernel to run", {
			cl_mem mA, mB, mC;
			std::vector<float> A,B,C;
			cl_context context;
			cl_command_queue queue;
			cl_program program;
			cl_kernel kernel;
			const size_t SIZE = 1024;
			
			BEFORE_EACH({
				context = CLHelper::create_context({device_id});
				queue = CLHelper::create_queue(context, device_id);
				program = CLHelper::create_program(context, {get_fn_kernel_source()});
				CLHelper::build_program(program, {device_id});
				kernel = CLHelper::create_kernel(program, "fn_kernel");
				
				A = std::vector<float>(SIZE);
				B = std::vector<float>(SIZE);
				C = std::vector<float>(SIZE);
				mA = CLHelper::create_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * SIZE);
				mB = CLHelper::create_buffer(context, CL_MEM_READ_ONLY, sizeof(float) * SIZE);
				mC = CLHelper::create_buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * SIZE);
		
				for(size_t i=0;i<SIZE;i++) {
					A[i] = i;
					B[i] = SIZE-i;
					C[i] = 0;
				}
			});
			AFTER_EACH({
				CLHelper::release_context(context);
				CLHelper::release_command_queue(queue);
				CLHelper::release_program(program);
				CLHelper::release_kernel(kernel);
				CLHelper::release_mem(mA);
				CLHelper::release_mem(mB);
				CLHelper::release_mem(mC);
			});
			
			IT("should succeed", {
				TEST_SUCCEED();
			});
			
			DESCRIBE("write data to device memory buffers", {
				cl_event ea, eb;
				BEFORE_EACH({
					ea = CLHelper::write(queue, mA, 0, SIZE * sizeof(float), A.data());
					eb = CLHelper::write(queue, mB, 0, SIZE * sizeof(float), B.data());
					CLHelper::await_events({ea, eb});
				});
				AFTER_EACH({
					CLHelper::release_event(ea);
					CLHelper::release_event(eb);
				});
				
				IT("should succeed", {
					TEST_SUCCEED();
				});
				
				IT("should successfully run kernel", {
					float alpha = 2.0;
					CLHelper::set_kernel_arg(kernel, 0, sizeof(float), &alpha);
					CLHelper::set_kernel_arg(kernel, 1, sizeof(cl_mem), &mA);
					CLHelper::set_kernel_arg(kernel, 2, sizeof(cl_mem), &mB);
					CLHelper::set_kernel_arg(kernel, 3, sizeof(cl_mem), &mC);
					cl_event er = CLHelper::run_kernel(queue, kernel, {0}, {SIZE}, {64});
					cl_event ec = CLHelper::read(queue, mC, 0, SIZE * sizeof(float), C.data(), {er});
					CLHelper::await_events({ec});
					for(size_t i=0;i<SIZE;i++) {
						EXPECT(C[i]).toBe(2048);
					}
				});
			});
		});
	});
});

SCENARIO_END
