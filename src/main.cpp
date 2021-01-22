#include <iostream>
#include <string>
#include <vector>
#include <CL/cl2.hpp>

namespace kernels::ocl {
    extern std::string kernel_add;
}


int main() {
    int error;

    auto platforms = std::vector<cl::Platform>();
    cl::Platform::get(&platforms);

    auto devices = std::vector<cl::Device>();
    platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &devices);

    auto ctx = cl::Context(devices, 0, 0, 0, &error);

    if (error != 0) {
        std::cout << "Cannot create context!" << std::endl;
        exit(-1);
    }

    auto queue = cl::CommandQueue(ctx, ctx.getInfo<CL_CONTEXT_DEVICES>()[0], CL_QUEUE_PROFILING_ENABLE, &error);

    if (error != 0) {
        std::cout << "Cannot create command queue!" << std::endl;
        exit(-1);
    }

    // Uncomment it if you want to know which device is being used.
    // std::cout << ctx.getInfo<CL_CONTEXT_DEVICES>()[0].getInfo<CL_DEVICE_NAME>() << std::endl;

    cl::Program program(ctx, kernels::ocl::kernel_add);
    error = program.build(devices);

    if (error != 0) {
        std::cout << "Cannot build kernel!" << std::endl;
        exit(-1);
    }

    cl::Kernel test_kernel(program, "gid");

    auto a = cl::Buffer(ctx, CL_MEM_READ_WRITE, 1024 * sizeof(unsigned int));

    test_kernel.setArg(0, a);

    cl::NDRange global(1024);
    cl::NDRange local(1024);

    unsigned int result[1024];

    error = queue.enqueueNDRangeKernel(test_kernel, cl::NullRange, global, local);
    queue.enqueueReadBuffer(a, CL_TRUE, 0, 1024 * sizeof(int), result);

    for (unsigned int i = 0; i < 1024; i++) {
        if (result[i] != i) {
            std::cout << "Wrong data returned from kernel!" << std::endl;
            exit(-1);
        }
    }

    std::cout << "Result is OK" << std::endl;

}
