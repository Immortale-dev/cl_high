#include "queue.hpp"

cl_high::Queue::Queue() {}

cl_high::Queue::Queue(cl_command_queue queue) : queue(queue) {}

cl_high::Queue::Queue(const Queue& instance) queue(instance.queue) {
	if (queue == nullptr) return;
	CLHelper::retain_command_queue(queue);
}

cl_high::Queue& cl_high::Queue::operator=(const Queue& instance) {
	if (queue != nullptr) {
		CLHelper::release_command_queue(queue);
	}
	queue = instance.queue;
	if (queue != nullptr) {
		CLHelper::retain_command_queue(queue);
	}
	return *this;
}

cl_high::Queue::~Queue() {
	if (queue == nullptr) return;
	CLHelper::release_command_queue(queue);
}

cl_command_queue cl_high::Queue::get() {
	return queue;
}

void cl_high::Queue::flush() {
	CLHelper::flush(queue);
}
