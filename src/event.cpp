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

void cl_high::Event::await(std::vector<Event> events) {
	std::vector<cl_event> event_ids;
	for(auto& it : events) {
		event_ids.push_back(it.get());
	}
	CLHelper::await_events(event_ids);
}

cl_event cl_high::Event::get() {
	return event;
}