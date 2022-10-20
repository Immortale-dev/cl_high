#ifndef CL_HIGH_PROGRAM_H_
#define CL_HIGH_PROGRAM_H_

#include <string>
#include <vector>

#include "cl_helper.hpp"
#include "context.hpp"
#include "kernel.hpp"
#include "job.hpp"

namespace cl_high {
	class Builder;
	
	class Program {
		Program(cl_program);
		friend Builder;
		
		public:
			Program();
			Program(const Program&);
			Program& operator=(const Program&);
			virtual ~Program();
			
			static from(Context context);
			
			Kernel create_kernel(std::string kernel_name);
			
			template<typename... Args>
			KernelJob prepare_kernel(std::string kernel_name, Args... args);
		
		private:
			cl_program program = nullptr;
	};
	class ProgramBuilder {
		ProgramBuilder() = delete;
		ProgramBuilder(Context context);
		
		public:
			Program build(Context context, std::vector<std::string> sources, std::string options);
			
		private:
			const Context context;
	};
}

template<typename... Args>
cl_high::KernelJob cl_high::Program::prepare_kernel(std::string kernel_name, Args... args) {
	Kernel kernel = create_kernel(kernel_name);
	return kernel.prepare(...args);
}

#endif // CL_HIGH_PROGRAM_H_