# OpenCL High

High level OpenCL library.

## Table of Contest

## Build

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
Defines **not** default constructable class used to create an instance of **cl_high::Buffer** class. The instance of this class can be created using [cl_high::Buffer::from()](#) method.

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
...




