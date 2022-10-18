#ifndef CL_HIGH_EVENT_
#define CL_HIGH_EVENT_

#include <memory>

#include "cl_helper.hpp"

namespace cl_high {
	class Event {
		Event(cl_event event);
		friend ComputeStation;
		
		public:
			Event();
			Event(const Event&);
			Event& operator=(const Event&);
			virtual ~Event();
			
			void await();
		
		private:
			cl_event event = nullptr;
	};
}

#endif // CL_HIGH_EVENT_