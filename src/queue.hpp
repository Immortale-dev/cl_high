#ifndef CL_HIGH_QUEUE_H_
#define CL_HIGH_QUEUE_H_

#include "cl_helper.hpp"

#include "context.hpp"

namespace cl_high {
	class Program;
	class ComputeStation;
	class Job;
	class ReadJob;
	class WriteJob;
	class KernelJob;
	
	class QueueBuilder;
	class Queue {
		Queue(cl_command_queue queue);
		friend Program;
		friend ComputeStation;
		friend Job;
		friend QueueBuilder;

		public:
			Queue();
			Queue(const Queue&);
			Queue& operator=(const Queue&);
			virtual ~Queue();
			static QueueBuilder from(Context context);
			void flush();

		private:
			cl_command_queue get();
		
			cl_command_queue queue = nullptr;
	};
	class QueueBuilder {
		friend Queue;
		QueueBuilder(Context context);
		QueueBuilder() = delete;

		public:
			Queue build();

		private:
			Context context;
	};
}

#endif // CL_HIGH_QUEUE_H_
