#ifndef GPU_CL_HELPER_H
#define GPU_CL_HELPER_H

#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

#include <vector>
#include <string>
#include <exception>
#include <cstring>

class CLHelper {
	public:
		class CLError : public std::exception {
			public:
				CLError(cl_int code, std::string additional = "") : msg(default_msg + std::to_string(code) + " " + additional) {}
				const char * what () const throw () {
					return msg.data();
				}
			
			private:
				const std::string default_msg = "CL operation failed with code: ";
				std::string msg;
		};
		
		struct PlatformInfo {
			std::string name;
			std::string vendor;
			std::string version;
		};

		struct DeviceInfo {
			cl_ulong global_mem_size;
			cl_ulong local_mem_size;
			cl_uint max_frequency;
			cl_uint max_compute_units;
			size_t max_work_group_size;
			std::string name;
			std::string vendor;
			std::string version;
		};
		
		static std::vector<cl_platform_id> get_platform_ids();
		static std::vector<cl_device_id> get_device_ids(cl_platform_id platform_id, cl_device_type device_type);
		static PlatformInfo get_platform_info(cl_platform_id platform_id);
		static DeviceInfo get_device_info(cl_device_id device_id);
		static cl_context create_context(std::vector<cl_device_id> device_ids);
		static cl_command_queue create_queue(cl_context context, cl_device_id device_id);
		static cl_mem create_buffer(cl_context context, cl_mem_flags flags, size_t size);
		static cl_event write(cl_command_queue queue, cl_mem buffer, size_t offset, size_t size, void *ptr, std::vector<cl_event> events = {});
		static cl_event read(cl_command_queue queue, cl_mem buffer, size_t offset, size_t size, void *ptr, std::vector<cl_event> events = {});
		static cl_program create_program(cl_context context, std::vector<std::string> sources);
		static void build_program(cl_program program, std::vector<cl_device_id> devices, std::string options = "");
		static std::string get_program_log(cl_program program, cl_device_id device_id);
		static cl_kernel create_kernel(cl_program program, std::string kernel_name);
		static void set_kernel_arg(cl_kernel kernel, cl_uint arg_index, size_t arg_size, void *arg_value);
		static cl_event run_kernel(cl_command_queue queue, cl_kernel kernel, const std::vector<size_t> offset, const std::vector<size_t> size, const std::vector<size_t> local_size, std::vector<cl_event> events = {});
		static void await_events(std::vector<cl_event>);
		static void flush(cl_command_queue queue);
		static void finish(cl_command_queue queue);
		static void release_kernel(cl_kernel kernel);
		static void release_program(cl_program program);
		static void release_mem(cl_mem mem);
		static void release_event(cl_event event);
		static void release_command_queue(cl_command_queue queue);
		static void release_context(cl_context context);
		static void retain_kernel(cl_kernel kernel);
		static void retain_program(cl_program program);
		static void retain_mem(cl_mem mem);
		static void retain_event(cl_event event);
		static void retain_command_queue(cl_command_queue queue);
		static void retain_context(cl_context context);
		
	private:
		inline static void confirm_status(cl_int status) {
			if (status != CL_SUCCESS) {
				throw CLError(status);
			}
		}
		static std::string get_platform_info_param(cl_platform_id platform_id, cl_platform_info param);
		static std::string get_device_info_param(cl_device_id device_id, cl_device_info param);
		static char* to_null_terminated_char_ptr(std::string);
};

#endif // GPU_CL_HELPER_H