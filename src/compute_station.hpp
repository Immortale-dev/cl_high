#ifndef CL_HIGH_COMPUTE_STATION_H_
#define CL_HIGH_COMPUTE_STATION_H_

#include <vector>
#include <string>

#include "cl_helper.h"
#include "device.hpp"
#include "context.hpp"
#include "queue.hpp"
#include "program.hpp"
#include "buffer.hpp"

namespace cl_high {
	class ComputeStation {
		ComputeStation(Device device);
		
		public:
			ComputeStation(const ComputeStation&);
			ComputeStation& operator=(const ComputeStation&);
			virtual ~ComputeStation();
			
			static ComputeStation from_device(Device device);
			
			Context get_context();
			Queue create_queue();
			Program build(std::vector<std::string> sources, std::string);
			
			Buffer create_buffer(AccessType type, size_t size);
			
		private:
			cl_device_id device_id;
			cl_context context;
	};
}

#endif // CL_HIGH_COMPUTE_STATION_H_