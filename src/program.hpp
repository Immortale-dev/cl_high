#ifndef CL_HIGH_PROGRAM_H_
#define CL_HIGH_PROGRAM_H_

#include <string>
#include <vector>

#include "cl_helper.hpp"
#include "context.hpp"
#include "kernel.hpp"
#include "event.hpp"

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
			// TODO
			Event run_kernel();
		
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

#endif // CL_HIGH_PROGRAM_H_