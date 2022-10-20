#ifndef CL_HIGH_KERNEL_
#define CL_HIGH_KERNEL_

#include <type_traits>

#include "cl_helper.h"
#include "job.hpp"

namespace cl_high {
	class Kernel {
		Kernel(cl_kernel);
		friend Program;
		
		public:
			Kernel();
			Kernel(const Kernel&);
			Kernel& operator=(const Kernel&);
			virtual ~Kernel();
			
			KernelJob prepare();
			
			template<typename... Args>
			KernelJob prepare(Args... args);
			
			template<typename... Args>
			void set_arguments(Args... args);
			
			template<typename T>
			void set_argument(const int arg_num, T arg);
			
		private:
			template<typename T, typename... Args>
			void prepare_unwrap(const int arg_num, T& arg, Args&... args);
			template<typename T>
			void prepare_unwrap(const int arg_num, T& arg);
			
			cl_kernel kernel = nullptr;
	};
}

cl_high::KernelJob cl_high::Kernel::prepare() {
	return KernelJob(kernel);
}

template<typename... Args>
cl_high::KernelJob cl_high::Kernel::prepare(Args... args) {
	prepare_unwrap(0, args...);
	return prepare();
}

template<typename... Args>
void cl_high::Kernel::set_arguments(Args... args) {
	prepare_unwrap(0, args...);
}

template<typename T>
void cl_high::Kernel::set_argument(const int arg_num, T arg) {
	prepare_unwrap(arg_num, arg);
}

template<typename T, typename... Args>
void cl_high::Kernel::prepare_unwrap(const int arg_num, T& arg, Args&... args) {
	prepare_unwrap(arg_num, arg);
	prepare_unwrap(arg_num + 1, args...);
}

template<typename T>
void cl_high::Kernel::prepare_unwrap(const int arg_num, T& arg){
	typename std::remove_pointer<T>::type* val;
	if (std::is_pointer<T>::value) {
		val = arg;
	} else {
		val = &arg;
	}
	CLHelper::set_kernel_arg(kernel, arg_num, sizeof(std::remove_pointer<T>::type), (void*)val);
}



#endif // CL_HIGH_KERNEL_