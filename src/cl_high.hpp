/**
 * OpenCL high level library.
 *
 * Contains public classes:
 * 
 * @class ComputeStation - main classes that keeps the Context and used to
 *        create computation queues.
 *   @public @static [ComputeStation] from_device(Device device) - used to
 *           create a compute station instance using the Device class instance.
 *   @public [Context] get_context() - returns a shared Context class instance
 *           connected to a device and used to create queues, buffers,
 *           programs, etc.
 *   @public [Queue] create_queue() - creates and returns a Queue class
 *           instance used to process data copy from/to device and process the
 *           kernal calculations.
 *   @public [Program] build(std::vector<std::string> sources [,
 *           std::string options]) - used to create and build a cl program and
 *           returns an instance of Program class.
 *   @public [Buffer] create_buffer(AccessType type, size_t size)
 * ------------------------------
 * @class Platform - describes open cl platform
 *   @public [const CLHelper::DeviceInfo&] get_info() - returns
 *           CLHelper::PlatformInfo class instance containing base information
 *           about the open cl platform.
 * ------------------------------
 * @class Devices - is a static class used to retrieve information about
 *        computation devices.
 *   @public @static [std::vector<Device>] cpu_devices() - returns a list of
 *           CPU devices.
 *   @public @static [std::vector<Device>] gpu_devices() - returns a list of
 *           GPU devices.
 *   @public @static [std::vector<Device>] all_devices() - returns a list of
 *           ALL compute devices.
 * ------------------------------
 * @class Device - is a class conntatining information about a single
 *        computation device.
 *   @public [const CLHelper::DeviceInfo&] get_info() - returns CLHelper::DeviceInfo
 *           class instance containing base information about the compute
 *           device.
 * ------------------------------
 * @class Context - keeps information about the context (device) for
 *        computations. Doesn't have public bembers.
 * ------------------------------
 * @class Queue - used to process data copy from/to device or process kernel
 *        computations.
 *   @public [void] flush() - flashes the queue and awaits for all the
 *           operations being processed on it to finish.
 * ------------------------------
 * @class Buffer used to create and operate with memory on device.
 *   @public @static [BufferBuilder] from(Context context) - returns
 *           BufferBuilder class instance used to create a buffer.
 *   @public [size_t] size() - returns the number of bytes the buffer owns.
 *   @public [void] release() - releases the buffers memory.
 *   @public [ReadJob] read<T>(T* ptr, size_t count[, size_t offset]) - returns
 *           a ReadJob class object used to run the data reading from device
 *           job.
 *   @public [WriteJob] write<T>(T* ptr, size_t count[, size_t offset]) -
 *           returns a WriteJob class object used to run the data writing to
 *           device job.
 * ------------------------------
 * @class BufferBuilder - used to create a Buffer.
 *   @public [Buffer] allocate(AccessType type, size_t size) - returns a Buffer
 *           that occupies `size` amount of memory on device.
 *   @public [Buffer] allocate<T>(AccessType type, size_t count) - returns a
 *           buffer that occupies `sizeof(T) * count` amount of bytes on
 *           device.
 * ------------------------------
 * @class Program - keeps information about compiler kernel functions on a
 *        device. It also allows to run the kernel functions on queues.
 *   @public @static [ProgramBuilder] from(Context context) - returns
 *           ProgramBuilder used to create and compile kernel programs.
 *   @public [Kernel] create_kernel(std::string kernel_name) - returns Kernel
 *           class instance.
 *   @public [KernelJob] prepare_kernel<Args...>(std::string kernel_name,
 *           Args... args) - returns a KernelJob class instanse used to run
 *           the kernel on a queue. It accepts the name of the kernel
 *           function and its arguments.
 * ------------------------------
 * @class ProgramBuilder - used to build the Program.
 *   @public [Program] build(std::vector<std::string> sources[,
 *           std::string options]) - creates and compiles kernel programs
 *           and returns Program class instance.
 *   @public [Program] build(std::string source[, std::string options]) -
 *           creates and compiles kernel programs and returns Program class
 *           instance.
 * ------------------------------
 * @class Kernel - used to run kernel functions on compute devices.
 *   @public [KernelJob] prepare() - returns a KernelJob class instance
 *           with empty kernel function parameters.
 *   @public [KernelJob] prepare<Args...>(Args... args) - returns a
 *           KernelJob class instance with assigned kernel function
 *           parameters.
 *   @public [void] set_arguments<Args...>(Args... args) - assigns
 *           arguments to the kernel instance.
 *   @public [void] set_argument<T>(const int arg_num, T arg) - assigns one
 *           argument to a kernel instance.
 * ------------------------------
 * @class ReadJob : Job - responsible for running the data read process from a
 *        device.
 *   @public [ReadJob&] on_queue(Queue queue) defines the queue to perform the
 *           job on.
 *   @public [ReadJob&] wait_for(std::vector<Event>) - defines events that
 *           have to be awaited before the read process.
 *   @public [Event] run() - starts the job.
 * ------------------------------
 * @class WriteJob : Job - responsible for running the data write process to a
 *        device.
 *   @public [WriteJob&] on_queue(Queue queue) defines the queue to perform the
 *           job on.
 *   @public [WriteJob&] wait_for(std::vector<Event>) - defines events that
 *           have to be awaited before the write process.
 *   @public [Event] run() - starts the job.
 * ------------------------------
 * @class KernelJob : Job - responsible for running the kernel function on a
 *        device.
 *   @public [KernelJob&] on_queue(Queue queue) defines the queue to perform
 *           the job on.
 *   @public [KernelJob&] wait_for(std::vector<Event>) - defines events that
 *           have to be awaited before the kernel function run process.
 *   @public [KernelJob&] with_parameters(size_t size, size_t local_size[,
 *           size_t offset, unsigned int work_dim]) - defines essentional
 *           parameters to run the kernel.
 *   @public [Event] run() - starts the job.
 * ------------------------------
 * @class Event - corresponding to the running job.
 *   @public [void] await() - awaits the job.
 *   @public @static [void] await(std::vector<Event> events) - awaits the list
 *           of jobs.
 */

#include "compute_station.hpp"
