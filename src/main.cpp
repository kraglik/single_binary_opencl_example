#include <iostream>
#include <string>
#include <vector>
#include <CL/cl2.hpp>

namespace kernels::ocl {
    extern std::string kernel_add;
}


int main() {
    auto platforms = std::vector<cl::Platform>();
    cl::Platform::get(&platforms);

    auto devices = std::vector<cl::Device>();
    platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &devices);

    auto ctx = cl::Context(devices);

    auto queue = cl::CommandQueue(ctx);

    std::cout << ctx.getInfo<CL_CONTEXT_DEVICES>()[0].getInfo<CL_DEVICE_NAME>() << std::endl;

    cl::Program program(ctx, kernels::ocl::kernel_add);
    program.build();

    cl::Kernel test_kernel(program, "gid");

    auto a = cl::Buffer(ctx, CL_MEM_READ_WRITE, 1024 * sizeof(unsigned int));

    test_kernel.setArg(0, a);

    cl::NDRange global(1024);
    cl::NDRange local(1024);

    unsigned int result[1024];

    auto error = queue.enqueueNDRangeKernel(test_kernel, cl::NullRange, global, local);
    std::cout << error << std::endl;
    queue.enqueueReadBuffer(a, CL_TRUE, 0, 1024 * sizeof(int), result);

    std::cout << result[11] << std::endl;
}