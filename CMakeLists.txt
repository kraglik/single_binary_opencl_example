cmake_minimum_required(VERSION 3.17)
project(single_binary_opencl_example)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCL REQUIRED)

set(GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")
set(GENERATED_INCLUDE_DIR "${GENERATED_DIR}/include")

file(MAKE_DIRECTORY ${GENERATED_INCLUDE_DIR})
include_directories(${GENERATED_INCLUDE_DIR})

set(CMAKE_MODULE_PATH
    "${single_binary_opencl_example_SOURCE_DIR}"
    "${single_binary_opencl_example_SOURCE_DIR}/cmake"
    "${single_binary_opencl_example_SOURCE_DIR}/cmake/utils"
    "${single_binary_opencl_example_SOURCE_DIR}/cmake/scripts"
)

include(preprocess_kernel)

include_directories(include ${OpenCL_INCLUDE_DIR})

set(EXECUTABLE_SRC
    ${single_binary_opencl_example_SOURCE_DIR}/src/main.cpp
)

set(OPENCL_KERNELS
    ${single_binary_opencl_example_SOURCE_DIR}/include/kernels/add.cl
)

set(generated_kernels_dir "${GENERATED_DIR}/opencl_kernels")
file(MAKE_DIRECTORY ${generated_kernels_dir})

preprocess_opencl_kernels(${generated_kernels_dir} kernels ${OPENCL_KERNELS})

set(OPENCL_SRCS_KERNELS
    ${generated_kernels_dir}/add_kernel.cpp
)

set(SINGLE_BINARY_OPENCL_SRCS
    ${EXECUTABLE_SRC}
    ${OPENCL_KERNELS}
    ${OPENCL_SRCS_KERNELS}
)

add_executable(single_binary_opencl_example ${SINGLE_BINARY_OPENCL_SRCS})
target_link_libraries(single_binary_opencl_example ${OpenCL_LIBRARIES})