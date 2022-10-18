#include "kernel.hpp"

cl_high::Kernel::Kernel(){}

cl_high::Kernel::Kernel(cl_kernel kernel) : kernel(kernel) {}

cl_high::Kernel::Kernel(const Kernel& instance) : kernel(instance.kernel) {
	if (kernel == nullptr) return;
	CLHelper::retain_kernel(kernel);
}

cl_hihg::Kernel& cl_high::Kernel::operator=(const Kernel& instance) {
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
