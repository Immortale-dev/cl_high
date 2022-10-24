#include "event.hpp"

cl_high::Event::Event() {}

cl_high::Event::Event(cl_event event) : event(event) {}

cl_high::Event::Event(const Event& instance) : event(instance.event) {
	if (event == nullptr) return;
	CLHelper::retain_event(event);
}

cl_high::Event& cl_high::Event::operator=(const Event& instance) {
	if (event != nullptr) {
		CLHelper::release_event(event);
	}
	event = instance.event;
	if (event != nullptr) {
		CLHelper::retain_event(event);
	}
	return *this;
}

cl_high::Event::~Event() {
	if (event == nullptr) return;
	CLHelper::release_event(event);
}

void cl_high::Event::await() {
	if (event == nullptr) return;
	CLHelper::await_events({event});
}

cl_event cl_high::Event::get() {
	return event;
}