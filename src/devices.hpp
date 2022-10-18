#ifndef CL_HIGH_DEVICES_H_
#define CL_HIGH_DEVICES_H_

#include <vector>
#include <stdexcept>

#include "cl_helper.hpp"

namespace cl_high {
	class ComputeStation;
	class Devices;
	
	class Device {
		public:
			Device();
			virtual ~Device();
			const DeviceInfo& get_info();
		
		private:
			Device(cl_device_id id, CLHelper::DeviceInfo info);
			cl_device_id get();
			
			const cl_device_id id;
			const CLHelper::DeviceInfo info;
			
			friend Devices;
			friend ComputeStation;
	};
	class Devices {
		Devices() = delete;
		
		public:
			static std::vector<Device> cpu_devices();
			static std::vector<Device> gpu_devices();
			static std::vector<Device> all_devices();
			
		private:
			static const cl_platform_id get_first_platform_id();
	};
}

#endif // CL_HIGH_DEVICES_H_
