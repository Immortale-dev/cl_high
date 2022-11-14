#include "queue.hpp"

cl_high::Queue::Queue() {}

cl_high::Queue::Queue(cl_command_queue queue) : queue(queue) {}

cl_high::Queue::Queue(const Queue& instance): queue(instance.queue) {
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

cl_high::QueueBuilder cl_high::Queue::from(Context context) {
	return QueueBuilder(context);
}

void cl_high::Queue::flush() {
	CLHelper::flush(queue);
}

cl_high::QueueBuilder::QueueBuilder(Context context): context(context) {}

cl_high::Queue cl_high::QueueBuilder::build() {
	return Queue(CLHelper::create_queue(context.get(), context.device()));
}