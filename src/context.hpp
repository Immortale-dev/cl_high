#ifndef CL_HIGH_CONTEXT_H_
#define CL_HIGH_CONTEXT_H_

#include "cl_helper.hpp"

namespace cl_high {
	class Builder;
	class ComputeStation;
	
	class Context {
		Context(cl_context context, cl_device_id device_id);
		friend ComputeStation;
		friend Builder;
		
		public:
			Context();
			virtual ~Context();
			
		private:
			cl_context get();
			cl_device_id device();
			
			const cl_context context;
			const cl_device_id device_id;
	};
}

#enfif // CL_HIGH_CONTEXT_H_
