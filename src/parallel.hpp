#ifndef PARALLEL_H_
#define PARALLEL_H_

#include <vector>
#include <string>
#include <memory>

namespace cl_high {
	class Devices;
	class Program;
	class ComputeStation;
	
	class ComputeStation {
		ComputeStation(Device device);
		
		public:
			ComputeStation(const ComputeStation&);
			ComputeStation& operator=(const ComputeStation&);
			virtual ~ComputeStation();
			
			static ComputeStation from_device(Device device);
			
			Context get_context();
			Queue create_queue();
			Program build(std::vector<std::string> sources);
			
			template<typename T>
			Buffer create_buffer(AccessType type, size_t size);
			
		private:
			const cl_device_id device_id;
			const cl_context;
	};
}

#endif PARALLEL_H_