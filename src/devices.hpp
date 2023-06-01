#ifndef CL_HIGH_DEVICES_H_
#define CL_HIGH_DEVICES_H_

#include <vector>
#include <stdexcept>

#include "cl_helper.hpp"

namespace cl_high {
	class ComputeStation;
	class Devices;
	
	class Platform {
		friend Devices;
		
		public:
			Platform();
			virtual ~Platform();
			const CLHelper::PlatformInfo& get_info();
		
		private:
			Platform(cl_platform_id id, CLHelper::PlatformInfo info);
			cl_platform_id get();
			
			const cl_platform_id id;
			const CLHelper::PlatformInfo info;
	};
	class Device {
		friend Devices;
		friend ComputeStation;
		
		public:
			Device();
			virtual ~Device();
			const CLHelper::DeviceInfo& get_info();
		
		private:
			Device(cl_device_id id, CLHelper::DeviceInfo info);
			cl_device_id get();
			
			const cl_device_id id;
			const CLHelper::DeviceInfo info;
	};
	class Devices {
		Devices() = delete;
		
		public:
			static std::vector<Platform> platforms();
			static std::vector<Device> cpu_devices(Platform platform = {});
			static std::vector<Device> gpu_devices(Platform platform = {});
			static std::vector<Device> all_devices(Platform platform = {});
			
		private:
			static const cl_platform_id get_first_platform_id();
	};
}

#endif // CL_HIGH_DEVICES_H_
