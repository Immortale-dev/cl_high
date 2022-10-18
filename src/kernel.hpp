#ifndef CL_HIGH_KERNEL_
#define CL_HIGH_KERNEL_

#include "cl_helper.h"

namespace cl_high {
	class Kernel {
		Kernel(cl_kernel);
		friend Program;
		
		public:
			Kernel();
			Kernel(const Kernel&);
			Kernel& operator=(const Kernel&);
			virtual ~Kernel();
			
			// TODO
			Event run();
			void set_arguments();
			void set_argument();
			
		private:
			cl_kernel kernel = nullptr;
	};
}

#endif // CL_HIGH_KERNEL_