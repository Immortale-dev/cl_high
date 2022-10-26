#ifndef CL_HIGH_EVENT_
#define CL_HIGH_EVENT_

#include <memory>
#include <vector>

#include "cl_helper.hpp"

namespace cl_high {
	class Job;
	class ReadJob;
	class WriteJob;
	class KernelJob;
	class Event {
		Event(cl_event event);
		friend Job;
		friend ReadJob;
		friend WriteJob;
		friend KernelJob;
		
		public:
			Event();
			Event(const Event&);
			Event& operator=(const Event&);
			virtual ~Event();
			
			void await();
			
			static void await(std::vector<Event> events);
		
		private:
			cl_event get();
		
			cl_event event = nullptr;
	};
}

#endif // CL_HIGH_EVENT_