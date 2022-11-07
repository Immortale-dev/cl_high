#include "job.hpp"

cl_high::Job::Job() {}

cl_high::Job::~Job() {}

cl_high::Job& cl_high::Job::on_queue(Queue queue) {
	this->queue = queue;
	return *this;
}

cl_high::Job& cl_high::Job::wait_for(std::vector<Event> events) {
	this->events = events;
	return *this;
}

std::vector<cl_event> cl_high::Job::get_event_id_list() {
	std::vector<cl_event> event_ids;
	for(auto& ev : events) {
		event_ids.push_back(ev.get());
	}
	return event_ids;
}

cl_command_queue cl_high::Job::get_queue() {
	return queue.get();
}

cl_high::ReadJob::ReadJob(cl_mem mem, void* ptr, size_t size, size_t offset): mem(mem), ptr(ptr), size(size), offset(offset) {
	CLHelper::retain_mem(mem);
}

cl_high::ReadJob::~ReadJob() {
	CLHelper::release_mem(mem);
}

cl_high::ReadJob& cl_high::ReadJob::on_queue(Queue queue) {
	Job::on_queue(queue);
	return *this;
}

cl_high::ReadJob& cl_high::ReadJob::wait_for(std::vector<Event> events) {
	Job::wait_for(events);
	return *this;
}

cl_high::Event cl_high::ReadJob::run() {
	return Event(CLHelper::read(get_queue(), mem, offset, size, ptr, get_event_id_list()));
}

cl_high::WriteJob::WriteJob(cl_mem mem, void* ptr, size_t size, size_t offset): mem(mem), ptr(ptr), size(size), offset(offset) {
	CLHelper::retain_mem(mem);
}

cl_high::WriteJob::~WriteJob() {
	CLHelper::release_mem(mem);
}

cl_high::WriteJob& cl_high::WriteJob::on_queue(Queue queue) {
	Job::on_queue(queue);
	return *this;
}

cl_high::WriteJob& cl_high::WriteJob::wait_for(std::vector<Event> events) {
	Job::wait_for(events);
	return *this;
}

cl_high::Event cl_high::WriteJob::run() {
	return Event(CLHelper::write(get_queue(), mem, offset, size, ptr, get_event_id_list()));
}

cl_high::KernelJob::KernelJob(cl_kernel kernel): kernel(kernel) {
	CLHelper::retain_kernel(kernel);
}

cl_high::KernelJob::~KernelJob() {
	CLHelper::release_kernel(kernel);
}

cl_high::KernelJob& cl_high::KernelJob::on_queue(Queue queue) {
	Job::on_queue(queue);
	return *this;
}

cl_high::KernelJob& cl_high::KernelJob::wait_for(std::vector<Event> events) {
	Job::wait_for(events);
	return *this;
}

cl_high::KernelJob& cl_high::KernelJob::with_parameters(size_t size, size_t local_size, size_t offset) {
	this->sizes = {size};
	this->local_sizes = {local_size};
	this->offsets = {offset};
	return *this;
}

cl_high::KernelJob& cl_high::KernelJob::with_parameters(std::vector<size_t> sizes, std::vector<size_t> local_sizes, std::vector<size_t> offsets) {
	this->sizes = sizes;
	this->local_sizes = local_sizes;
	this->offsets = offsets;
	return *this;
}

cl_high::Event cl_high::KernelJob::run() {
	return Event(CLHelper::run_kernel(get_queue(), kernel, offsets, sizes, local_sizes, get_event_id_list()));
}
