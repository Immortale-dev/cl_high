#ifndef CL_HIGH_QUEUE_H_
#define CL_HIGH_QUEUE_H_

#include "cl_helper.hpp"

namespace cl_high {
	class Program;
	class ComputeStation;
	class Job;
	class ReadJob;
	class WriteJob;
	class KernelJob;
	
	class Queue {
		Queue(cl_command_queue queue);
		friend Program;
		friend ComputeStation;
		friend Job;

		public:
			Queue();
			Queue(const Queue&);
			Queue& operator=(const Queue&);
			virtual ~Queue();
			void flush();

		private:
			cl_command_queue get();
		
			cl_command_queue queue = nullptr;
	};
}

#endif // CL_HIGH_QUEUE_H_
