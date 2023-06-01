#include "buffer.hpp"

cl_high::Buffer::Buffer() : size_bytes(0) {}

cl_high::Buffer::Buffer(cl_mem mem, AccessType type, size_t size_bytes) : mem(mem), type(type), size_bytes(size_bytes) {}

cl_high::Buffer::Buffer(const Buffer& instance) : mem(instance.mem), type(instance.type), size_bytes(instance.size_bytes) {
	if (mem == nullptr) return;
	CLHelper::retain_mem(mem);
}

cl_high::Buffer& cl_high::Buffer::operator=(const Buffer& instance) {
	if (mem != nullptr) {
		CLHelper::release_mem(mem);
	}
	mem = instance.mem;
	type = instance.type;
	size_bytes = instance.size_bytes;
	if (mem != nullptr) {
		CLHelper::retain_mem(mem);
	}
	return *this;
}

cl_high::Buffer::~Buffer() {
	release();
}

void cl_high::Buffer::release() {
	if (mem == nullptr) return;
	CLHelper::release_mem(mem);
	mem = nullptr;
}

size_t cl_high::Buffer::size() {
	return size_bytes;
}

bool cl_high::Buffer::empty() {
	return size() == 0;
}

cl_mem& cl_high::Buffer::get() {
	return mem;
}

cl_high::BufferBuilder cl_high::Buffer::from(Context context) {
	return BufferBuilder(context);
}

cl_high::BufferBuilder::BufferBuilder(Context context): context(context) {}

cl_high::Buffer cl_high::BufferBuilder::allocate(AccessType type, size_t size) {
	return Buffer(CLHelper::create_buffer(context.get(), static_cast<cl_mem_flags>(type), size), type, size);
}
