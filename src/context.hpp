#ifndef CL_HIGH_CONTEXT_H_
#define CL_HIGH_CONTEXT_H_

#include "cl_helper.hpp"

namespace cl_high {
	class ProgramBuilder;
	class BufferBuilder;
	class QueueBuilder;
	class ComputeStation;
	
	class Context {
		Context(cl_context context, cl_device_id device_id);
		friend ProgramBuilder;
		friend QueueBuilder;
		friend BufferBuilder;
		friend ComputeStation;
		
		public:
			Context();
			virtual ~Context();
			
		private:
			cl_context get() const;
			cl_device_id device() const;
			
			const cl_context context;
			const cl_device_id device_id;
	};
}

#endif // CL_HIGH_CONTEXT_H_
