#ifndef CL_HIGH_JOB_H_
#define CL_HIGH_JOB_H_

#include <vector>

#include "cl_helper.h"
#include "queue.hpp"
#include "event.hpp"

namespace cl_high {
	class Buffer;
	class Kernel;
	class Job {
		public:
			Job();
			virtual ~Job();
			Job& on_queue(Queue);
			Job& wait_for(std::vector<Event>);
			virtual Event run() = 0;
		
		private:
			Queue queue;
			std::vector<Event> events;
	};
	class ReadJob : public Job {
		ReadJob() = delete;
		friend Buffer;
		
		public:
			~ReadJob();
			Event run();
		
		private:
			ReadJob(cl_mem mem, void* ptr, size_t size, size_t offset);
			
			const cl_mem mem;
			const void* ptr;
			const size_t size;
			const size_t offset;
	};
	class WriteJob : public Job {
		WriteJob() = delete;
		friend Buffer;
		
		public:
			~WriteJob();
			Event run();
			
		private:
			WriteJob(cl_mem mem, void* ptr, size_t size, size_t offset);
			
			const cl_mem mem;
			const void* ptr;
			const size_t size;
			const size_t offset;
	};
	class KernelJob : public Job {
		KernelJob() = delete;
		friend Kernel;
		
		public:
			~KernelJob();
			KernelJob& withParameters(size_t size, size_t local_size, size_t offset = 0, unsigned int work_dim = 1);
			Event run();
			
		private:
			KernelJob(cl_kernel kernel);
			
			const cl_kernel kernel;
			size_t size;
			size_t local_size;
			size_t offset;
			cl_uint work_dim;
	};
}

#endif // CL_HIGH_JOB_H_