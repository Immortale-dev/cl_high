# OpenCL High

High level **C++** [OpenCL](https://registry.khronos.org/OpenCL/sdk/1.0/docs/man/xhtml/) library.

## Table of Contest
* [OpenCL High](#opencl-high)
	* [Table of Contest](#table-of-contest)
	* [Build](#build)
		* [Dependencies](#dependencies)
		* [Run](#run)
	* [Documentation](#documentation)
		* [cl_high namespace](#cl_high-namespace)
		* [class cl_high::ComputeStation](#class-cl_highcomputestation)
			* [static cl_high::ComputeStation from_device(Device device)](#static-cl_highcomputestation-from_devicedevice-device)
			* [cl_high::Context get_context()](#cl_highcontext-get_context)
			* [cl_high::Queue create_queue()](#cl_highqueue-create_queue)
			* [cl_high::Program build(std::vector\<std::string\> sources\[, std::string options\])](#cl_highprogram-buildstdvectorstdstring-sources-stdstring-options)
			* [cl_high::Program build(std::string source\[, std::string options\])](#cl_highprogram-buildstdstring-source-stdstring-options)
			* [cl_high::Buffer create_buffer(cl_high::AccessType type, size_t size)](#cl_highbuffer-create_buffercl_highaccesstype-type-size_t-size)
			* [cl_high::Buffer create_buffer\<T\>(cl_high::AccessType type, size_t count)](#cl_highbuffer-create_buffertcl_highaccesstype-type-size_t-count)
		* [class cl_high::Devices](#class-cl_highdevices)
			* [static std::vector\<Platform\> platforms()](#static-stdvectorplatform-platforms)
			* [static std::vector\<Device\> all_devices(\[cl_high::Platform platform\])](#static-stdvectordevice-all_devicescl_highplatform-platform)
			* [static std::vector\<Device\> cpu_devices(\[cl_high::Platform platform\])](#static-stdvectordevice-cpu_devicescl_highplatform-platform)
			* [static std::vector\<Device\> gpu_devices(\[cl_high::Platform platform\])](#static-stdvectordevice-gpu_devicescl_highplatform-platform)
		* [class cl_high::Platform](#class-cl_highplatform)
			* [const CLHelper::PlatformInfo& get_info()](#const-clhelperplatforminfo-get_info)
		* [class cl_high::Device](#class-cl_highdevice)
			* [const CLHelper::DeviceInfo& get_info()](#const-clhelperdeviceinfo-get_info)
		* [class cl_high::Context](#class-cl_highcontext)
		* [class cl_high::Queue](#class-cl_highqueue)
			* [void flush()](#void-flush)
		* [class cl_high::Buffer](#class-cl_highbuffer)
			* [static cl_high::BufferBuilder from(cl_high::Context context)](#static-cl_highbufferbuilder-fromcl_highcontext-context)
			* [size_t size()](#size_t-size)
			* [void release()](#void-release)
			* [cl_high::ReadJob read\<T\>(T* ptr, size_t count\[, size_t offset\])](#cl_highreadjob-readtt-ptr-size_t-count-size_t-offset)
			* [cl_high::WriteJob write\<T\>(T* ptr, size_t count\[, size_t offset\])](#cl_highwritejob-writett-ptr-size_t-count-size_t-offset)
		* [class cl_high::BufferBuilder](#class-cl_highbufferbuilder)
			* [cl_high::Buffer allocate(cl_high::AccessType, size_t size)](#cl_highbuffer-allocatecl_highaccesstype-size_t-size)
			* [cl_high::Buffer allocate\<T\>(cl_high::AccessType type, size_t count)](#cl_highbuffer-allocatetcl_highaccesstype-type-size_t-count)
		* [class cl_high::Program](#class-cl_highprogram)
			* [static cl_high::ProgramBuilder from(cl_high::Context context)](#static-cl_highprogrambuilder-fromcl_highcontext-context)
			* [cl_high::Kernel create_kernel(std::string kernel_name)](#cl_highkernel-create_kernelstdstring-kernel_name)
			* [cl_high::KernelJob prepare_kernel\<Args…\>(std::string kernel_name, Args… args)](#cl_highkerneljob-prepare_kernelargs...stdstring-kernel_name-args...-args)
		* [class cl_high::ProgramBuilder](#class-cl_highprogrambuilder)
			* [cl_high::Program build(std::string source\[, std::string options\])](#cl_highprogram-buildstdstring-source-stdstring-options-1)
			* [cl_high::Program build(std::vector\<std::string\> sources\[, std::string options\])](#cl_highprogram-buildstdvectorstdstring-sources-stdstring-options-1)
		* [class cl_high::Kernel](#class-cl_highkernel)
			* [cl_high::KernelJob prepare()](#cl_highkerneljob-prepare)
			* [cl_high::KernelJob prepare\<Args…\> prepare(Args… args)](#cl_highkerneljob-prepareargs...-prepareargs...-args)
			* [void set_arguments\<Args…\> set_arguments(Args… args)](#void-set_argumentsargs...-set_argumentsargs...-args)
			* [void set_argument\<\T\>(const int arg_num, T arg)](#void-set_argumenttconst-int-arg_num-t-arg)
		* [class cl_high::ReadJob : Job](#class-cl_highreadjob--job)
			* [cl_high::ReadJob& on_queue(Queue queue)](#cl_highreadjob-on_queuequeue-queue)
			* [cl_high::ReadJob& wait_for(std::vector\<cl_high::Event\>)](#cl_highreadjob-wait_forstdvectorcl_highevent)
			* [cl_high::Event run()](#cl_highevent-run)
		* [class cl_high::WriteJob : Job](#class-cl_highwritejob--job)
			* [cl_high::WriteJob& on_queue(Queue queue)](#cl_highwritejob-on_queuequeue-queue)
			* [cl_high::WriteJob& wait_for(std::vector\<cl_high::Event\>)](#cl_highwritejob-wait_forstdvectorcl_highevent)
			* [cl_high::Event run()](#cl_highevent-run-1)
		* [class cl_high::KernelJob : Job](#class-cl_highkerneljob--job)
			* [cl_high::KernelJob& on_queue(Queue queue)](#cl_highkerneljob-on_queuequeue-queue)
			* [cl_high::KernelJob& wait_for(std::vector\<cl_high::Event\>)](#cl_highkerneljob-wait_forstdvectorcl_highevent)
			* [cl_high::KernelJob& with_parameters(size_t size, size_t loacl_size\[, size_t offset, unsigned int work_dim\])](#cl_highkerneljob-with_parameterssize_t-size-size_t-loacl_size-size_t-offset-unsigned-int-work_dim)
			* [cl_high::Event run()](#cl_highevent-run-2)
		* [class cl_high::Event](#class-cl_highevent)
			* [void await()](#void-await)
			* [static void await(std::event\<cl_high::Event\>)](#static-void-awaitstdeventcl_highevent)
	* [Usage Example](#usage-example)
	* [Tests](#tests)
	* [License](#license)

## Build

### Dependencies
There is only one dependency - **OpenCL**. You can install it from the offical video card provider website. For example: [Nvidia](https://developer.nvidia.com/opencl)

To build the library you need to add path to OpenCL header files and link the OpenCL shared library to the compiler. The example of how to do it provided in the **makefile** in the root directory of this repository.

The library was tested using **GNU** compiler using **C++14** and heigher specifiction.

### Run
You can build unit tests uning **make all** (default) command, this will generate **test.exe** file in the root folder if this repository, also you can build *sandbox* (test/mtest.cpp) file using **make custom** command, to play around. It will generate **mtest.exe** file in the root directory.

## Documentation

### cl_high namespace
The library defines **cl_high** namespace containing a banch of useful classes. 

___

### class cl_high::ComputeStation
Defines main *compute* class. It owns a **Context** corresponding to a device, used to creates **Queue** instances and provides handy methods for building programs, creating buffers, etc. 

#### static cl_high::ComputeStation from_device(Device device)
Creates a **ComputeStation** instance using the **Device** class instance.

***Example:***
```c++
auto station = cl_high::ComputeStation::from_device(cl_high::Devices::gpu_devices()[0]);
```

#### cl_high::Context get_context()
Returns a shared **cl_high::Context** class instance connected to a device and used to create queues, buffers, programs, etc.

#### cl_high::Queue create_queue()
Creates and returns new **cl_high::Queue** class instance used to read/write data into device and run kernel functions.

#### cl_high::Program build(std::vector\<std::string\> sources[, std::string options])
Create and compiles kernel program from sources. Returns an instance of **cl_high::Program** class.

With the list of sources you can also optionally provide the list of **options** defined on the [page](https://registry.khronos.org/OpenCL/sdk/1.0/docs/man/xhtml/clBuildProgram.html)

#### cl_high::Program build(std::string source[, std::string options])
Same as above, but instead of the list of sources, accepts single string source.

***Example:***
```c++
std::string source = 
"__kernel                                                       \n"
"void kernel_fn(float a, __global float* b, __global float* c)  \n"
"{                                                              \n"
"    int index = get_global_id(0);                              \n"
"    c[index] = a * b[index];                                   \n"
"}                                                              \n";

// Defines compute station
cl_high::ComputeStation station = ...;

// Creates and builds program
cl_high::Program = station.build(source);
```

#### cl_high::Buffer create_buffer(cl_high::AccessType type, size_t size)
Allocates buffer memory on device. **type** can be **READ**, **WRITE**, or **READWRITE**, and **size** corresponds to the amount of bytes allocated on the device.
Returns **cl_high::Buffer** class instance.

#### cl_high::Buffer create_buffer\<T\>(cl_high::AccessType type, size_t count)
Same as above, but with the difference, that amount of bytes allocated on a device equals `count * sizeof(T)`.

___

### class cl_high::Devices
Contains only static methods that help working with devices and platforms.

#### static std::vector\<Platform\> platforms()
Returns the list of platforms available on the machine.

#### static std::vector\<Device\> all_devices([cl_high::Platform platform])
Returns the list of all devices on a platform. **platform** is an optional parameters, if not provided, the first available platform will be used.

#### static std::vector\<Device\> cpu_devices([cl_high::Platform platform])
Same as above, but returns only *CPU* devices.

#### static std::vector\<Device\> gpu_devices([cl_high::Platform platform])
Same as above, but returns only *GPU* devices.

___

### class cl_high::Platform
Defines *OpenCL* platform on the machine.

#### const CLHelper::PlatformInfo& get_info()
Returns the basic information about the platform.

**CLHelper::PlatformInfo** contains next public members:
* **std::string** name
* **std::string** vendor
* **std::string** version

___

### class cl_high::Device
Defines *OpenCL* device on the platform.

#### const CLHelper::DeviceInfo& get_info()
Returns the basic information about the device.

**CLHelper::DeviceInfo** contains next public members:
* **cl_ulong** global_mem_size
* **cl_ulong** local_mem_size
* **cl_uint** max_frequency
* **cl_uint** max_compute_units
* **size_t** max_work_group_size
* **std::string** name
* **std::string** vendor
* **std::string** version

___

### class cl_high::Context
Keeps information about the context and its device. A context used to provide some inforamtion about the device to other classes and structures. It's doesn't have any public members.

___

### class cl_high::Queue
Used to process the data read/write from or to computation device and run kernel functions.

#### void flush()
blocks current thread and awaits all the operations at the queue to finish.

___

### class cl_high::Buffer
Used to allocate and keep memory on a *device*. Can be created using **cl_high::BufferBuilder** class or from the **cl_high::ComputeStation** class instance using **create_buffer** method.

#### static cl_high::BufferBuilder from(cl_high::Context context)
Returns **cl_high::BufferBuider** class instance used to create **cl_high::Buffer** class instance.

***Example:***
```c++
cl_high::ComputeStation station = ...;

// Allocates sizeof(float) * 1000 bytes of memory on device
Buffer b = Buffer::from(station.get_context()).allocate<float>(1000);
```

#### size_t size()
Returns the number of allocated bytes on device.

#### void release()
Releases the memory allocated on device.

#### cl_high::ReadJob read\<T\>(T* ptr, size_t count[, size_t offset])
Creates and returns a **cl_high::ReadJob** class instance and prepares to read the `sizeof(T) * count` bytes of data with offset equals to `sizeof(T) * offset` bytes from *device* to **ptr**.

***Note:*** this method doesn't read the data, but just *prepare* the data to be read.

#### cl_high::WriteJob write\<T\>(T* ptr, size_t count[, size_t offset])
Creates and returns a **cl_high::WriteJob** class instance and prepares to write the `sizeof(T) * count` bytes of data with the offset equals to `sizeof(T) * offset` to *device* from **ptr**.

***Note:*** this method doesn't write the data, but just *prepare& the data to be written.

___

### class cl_high::BufferBuilder
Defines **not** default constructable class used to create an instance of **cl_high::Buffer** class. The instance of this class can be created using [cl_high::Buffer::from()](#static-cl_highbufferbuilder-fromcl_highcontext-context) method.

#### cl_high::Buffer allocate(cl_high::AccessType, size_t size)
Allocates **size** bytes on a device with an access level equals to **type** and returns an instance of **cl_high::Buffer** class.

#### cl_high::Buffer allocate\<T\>(cl_high::AccessType type, size_t count)
Allocates `sizeof(T) * count` bytes of memory on a device with an access level equals to **type** and returns an instance of **cl_high::Buffer** class.

___

### class cl_high::Program
Keeps information about compiled kernel functions on a device, and provides methods to run the *kernels* on a specific queue.

#### static cl_high::ProgramBuilder from(cl_high::Context context)
Returns an instance of **cl_high::ProgramBuilder** class used to create and build kernel programs.

#### cl_high::Kernel create_kernel(std::string kernel_name)
Creates and returns an instance of **cl_high::Kernel** class used to prepare the kernel to run on a specific *queue*.

#### cl_high::KernelJob prepare_kernel<Args...>(std::string kernel_name, Args... args)
Creates and returns an instance of **cl_high::KernelJob** used to run the kernel. It accepts the name of the kernel function, and a list of arguments the kernal program should use.

***Example:***
```c++
cl_high::ComputeStation station = ...;
cl_high::Program prog = station.build(sources);
cl_high::Queue queue = station.create_queue();

cl_high::Buffer bIn = station.create_buffer<float>(cl_high::AccessType::READ, 1000);
cl_high::Buffer bOut = station.create_buffer<float(cl_high::AccessType::WRITE, 1000);

// Fill the input buffer
cl_high::KernelJob job = prog.prepare_kernel("kernel_fn", bIn, bOut);

// Runs kernel function
job.on_queue(queue).with_parameters(1000, 25).run();
```

___

### class cl_high::ProgramBuilder
Is a **non** default constructable class used to create an instance of **cl_high::Program** class.

#### cl_high::Program build(std::string source[, std::string options])
Creates and builds kernel source and returns an instance of **cl_high::Program** class.

#### cl_high::Program build(std::vector\<std::string\> sources[, std::string options])
The same as above, but multiple sources can be provided as a vector of strings.

___

### class cl_high::Kernel
Corresponding to the single *kernel* function, and provides methods to prepared the kernel to run.

#### cl_high::KernelJob prepare()
Prepares the kernel to run **without** assigning values to arguments, and returns **cl_high::KernelJob** class instance providing the methods to run the *kernel* on a specific queue.

#### cl_high::KernelJob prepare\<Args...\> prepare(Args... args)
Same as above, but assigns values to the kernel's arguments.

#### void set_arguments\<Args...\> set_arguments(Args... args)
Assigns values to the kernel's arguments.

#### void set_argument<\T\>(const int arg_num, T arg)
Assigns single value to the kernel's argument.

___

### class cl_high::ReadJob : Job
Runs read *event* (job) on a specific queue and with specific parameters.

#### cl_high::ReadJob& on_queue(Queue queue)
Defines the queue on which the job will run. 

***Note:*** returns **\*this**.

#### cl_high::ReadJob& wait_for(std::vector\<cl_high::Event\>)
Defines *events* (jobs that are beigb processed) that needs to be awaited before the read job can be started.

***Note:*** returns **\*this**.

#### cl_high::Event run()
Runs the job and returns the instance of **cl_high::Event** class that can be awaited manually, or sent to other job and block it until the event is finished.

___

### class cl_high::WriteJob : Job
Runs write *event* (job) on a specific queue and with specific parameters.

#### cl_high::WriteJob& on_queue(Queue queue)
Defines the queue on which the job will run. 

***Note:*** returns **\*this**.

#### cl_high::WriteJob& wait_for(std::vector\<cl_high::Event\>)
Defines *events* (jobs that are beigb processed) that needs to be awaited before the write job can be started.

***Note:*** returns **\*this**.

#### cl_high::Event run()
Runs the job and returns the instance of **cl_high::Event** class that can be awaited manually, or sent to other job and block it until the event is finished.

___

### class cl_high::KernelJob : Job
Runs kernel *event* (job) on as specific queue and with specific parameters.

#### cl_high::KernelJob& on_queue(Queue queue)
Defines the queue on which the job will run. 

***Note:*** returns **\*this**.

#### cl_high::KernelJob& wait_for(std::vector\<cl_high::Event\>)
Defines *events* (jobs that are beigb processed) that needs to be awaited before the kernel job can be started.

***Note:*** returns **\*this**.

#### cl_high::KernelJob& with_parameters(size_t size, size_t loacl_size[, size_t offset])
Defines global and local sizes to run the kernel as well as the offset and number of working dimenions. **offset** is optional. If not apssed, `0` will be assigned. Work dimension is `1`. More information about these parameters can be found on [opencl doc](https://registry.khronos.org/OpenCL/sdk/1.0/docs/man/xhtml/clEnqueueNDRangeKernel.html).

#### cl_high::KernelJob& with_parameters(std::vector\<size_t\> sizes, std::vector\<size_t\> local_sizes[, std::vector\<size_t\> offsets])
Same as above, but work dimentions equals to the size of **sizes** vector, and parameters are provided for each working directory using *std::vector* structures.

***Note:*** the size of the **sizes**, **local_sizes**, and **offsets** (if provided) vectors must be the same.

#### cl_high::Event run()
Runs the job and returns the instance of **cl_high::Event** class that can be awaited manually, or sent to other job and block it until the event is finished.

___

### class cl_high::Event
Defines running *event* (job), and provides methods to block current thread and wait for the event to finish.

#### void await()
Blocks current thread and waits the event (job) to finish.

#### static void await(std::event\<cl_high::Event\>)
Static method to await a list of events.

___

## Usage Example
Next program adds 2 vectors with additional multiplication parameter.

```c++
#include <string>
#include <vector>

// Include the library
#include "cl_high.hpp"

// Kernel source code
const std::string source = 
	"__kernel                                      \n"
	"void fn_kernel(float alpha,                   \n"
	"                  __global float *A,          \n"
	"                  __global float *B,          \n"
	"                  __global float *C)          \n"
	"{                                             \n"
	"    //Get the index of the work-item          \n"
	"    int index = get_global_id(0);             \n"
	"                                              \n"
	"    C[index] = alpha * (A[index] + B[index]); \n"
	"                                              \n"
	"}                                             \n";

// Size of vectors
const size_t SIZE = 1000;

int main() {
	auto station = cl_high::ComputeStation::from_device(Devices::gpu_devices()[0]);

	cl_high::Queue queue = compute.create_queue();
	cl_high::Program = compute.build(source);

	cl_high::Buffer b_a = station.createBuffer<float>(cl_high::AccessType::READ, SIZE);
	cl_high::Buffer b_b = station.createBuffer<float>(cl_high::AccessType::READ, SIZE);
	cl_high::Buffer b_c = station.createBuffer<float>(cl_high::AccessType::WRITE, SIZE);

	std::vector<float> a(SIZE), b(SIZE), c(SIZE);

	// Fill original data
	for(size_t i=0;i<SIZE;i++){
		a[i] = i;
		b[i] = SIZE-i;
		c[i] = 0;
	}

	// Write data to on device
	cl_high::Event e_a = b_a.write(a.data(), SIZE).on_queue(queue).run();
	cl_high::Event e_b = b_b.write(b.data(), SIZE).on_queue(queue).run();

	// Await write jobs and run the kernel
	cl_high::Event e_k = program.prepare_kernel("fn_kernel", (float)3.0, b_a, b_b, b_c).on_queue(queue).await_for({e_a, e_b}).with_parameters(SIZE, 25).run();

	// Await kernel job and read the data
	auto e_c = b_c.read(c.data(), SIZE).on_queue(queue).await_for({e_k}).run();

	// Await read job
	e_c.await();
	
	// Data is read
	for(size_t i=0;i<SIZE;i++){
		assert(c[i] == 3000);
	}

	return 0;
}
```

## Tests
Regular unit tests are placed under the **tests** folder.

To build test files you can run the `make` command in the terminal. The script will generate **test.exe** file in the root directory of the repository.

## License
MIT

Have fun! :)