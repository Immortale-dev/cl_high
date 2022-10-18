#ifndef CL_HIGH_BUFFER_H_
#define CL_HIGH_BUFFER_H_

#include "cl_helper.hpp"
#include "context.hpp"
#include "event.hpp"

namespace cl_high {
	class Kernel;
	
	enum class AccessType {
		READ = CL_MEM_READ_ONLY,
		WRITE = CL_MEM_WRITE_ONLY,
		READ_WRITE = CL_MEM_READ_WRITE
	};
	
	class Buffer {
		friend Kernel;
		
		Buffer(cl_mem, AccessType, size_t);
		
		public:
			Buffer();
			Buffer(const Buffer&);
			Buffer& operator=(const Buffer&);
			virtual ~Buffer();
			
			void release();
			size_t size();
			
			static BufferBuilder from(Context context);
			
			// TODO:
			Event read();
			Event write();
			
		private:
			cl_mem mem = nullptr;
			AccessType type;
			size_t size_bytes;
	};
	class BufferBuilder {
		friend Buffer;
		BufferBuilder() = delete;
		BufferBuilder(Context context);
		
		public:
			Buffer allocate(AccessType type, size_t size);
			
		private:
			const Context context;
	};
}

#endif // CL_HIGH_BUFFER_H_