#include "kernel.hpp"

cl_high::Kernel::Kernel(){}

cl_high::Kernel::Kernel(cl_kernel kernel) : kernel(kernel) {}

cl_high::Kernel::Kernel(const Kernel& instance) : kernel(instance.kernel) {
	if (kernel == nullptr) return;
	CLHelper::retain_kernel(kernel);
}

cl_high::Kernel& cl_high::Kernel::operator=(const Kernel& instance) {
	if (kernel != nullptr) {
		CLHelper::release_kernel(kernel);
	}
	kernel = instance.kernel;
	if (kernel != nullptr) {
		CLHelper::retain_kernel(kernel);
	}
	return *this;
}

cl_high::Kernel::~Kernel() {
	if (kernel == nullptr) return;
	CLHelper::release_kernel(kernel);
}

cl_high::KernelJob cl_high::Kernel::prepare() {
	return KernelJob(kernel);
}

void cl_high::Kernel::prepare_unwrap(const int arg_num, Buffer& arg) {
	CLHelper::set_kernel_arg(kernel, arg_num, sizeof(cl_mem), &arg.get());
}
