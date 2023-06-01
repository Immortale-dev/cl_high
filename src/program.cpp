#include "program.hpp"

cl_high::Program::Program() {}

cl_high::Program::Program(cl_program program) : program(program) {}

cl_high::Program::Program(const Program& instance) : program(instance.program) {
	if (program == nullptr) return;
	CLHelper::retain_program(program);
}

cl_high::Program& cl_high::Program::operator=(const Program& instance) {
	if (program != nullptr) {
		CLHelper::release_program(program);
	}
	program = instance.program;
	if (program != nullptr) {
		CLHelper::retain_program(program);
	}
	return *this;
}

cl_high::Program::~Program() {
	if (program == nullptr) return;
	CLHelper::release_program(program);
}

cl_high::ProgramBuilder cl_high::Program::from(Context context) {
	return ProgramBuilder(context);
}

cl_high::Kernel cl_high::Program::create_kernel(std::string kernel_name) {
	return Kernel(CLHelper::create_kernel(program, kernel_name));
}

cl_high::ProgramBuilder::ProgramBuilder(Context context): context(context) {}

cl_high::Program cl_high::ProgramBuilder::build(std::string source, std::string options) {
	return build(std::vector<std::string>(1, source), options);
}

cl_high::Program cl_high::ProgramBuilder::build(std::vector<std::string> sources, std::string options) {
	cl_program program = CLHelper::create_program(context.get(), sources);
	CLHelper::build_program(program, {context.device()}, options);
	return Program(program);
}
