#ifndef CL_HIGH_COMPUTE_STATION_H_
#define CL_HIGH_COMPUTE_STATION_H_

#include <vector>
#include <string>

#include "cl_helper.hpp"
#include "devices.hpp"
#include "context.hpp"
#include "queue.hpp"
#include "program.hpp"
#include "buffer.hpp"

namespace cl_high {
	class ComputeStation {
		ComputeStation(Device device);
		
		public:
			ComputeStation();
			ComputeStation(const ComputeStation&);
			ComputeStation& operator=(const ComputeStation&);
			virtual ~ComputeStation();
			
			static ComputeStation from_device(Device device);
			
			Context get_context();
			Queue create_queue();
			Program build(std::vector<std::string> sources, std::string options = "");
			Program build(std::string source, std::string options = "");
			Buffer create_buffer(AccessType type, size_t size);
			
			template<typename T>
			Buffer create_buffer(AccessType type, size_t count);
			
		private:
			cl_device_id device_id;
			cl_context context;
	};
}

template<typename T>
cl_high::Buffer cl_high::ComputeStation::create_buffer(AccessType type, size_t count) {
	return Buffer::from(get_context()).allocate<T>(type, count);
}

#endif // CL_HIGH_COMPUTE_STATION_H_