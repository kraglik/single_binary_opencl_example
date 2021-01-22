function(preprocess_opencl_kernel NAMESPACE KERNEL SRC DST)
    message(STATUS "Preprocessing OpenCL kernel: " ${SRC} " => " ${DST} )
    add_custom_command(
        OUTPUT ${DST}
        COMMAND ${CMAKE_COMMAND}
        -DDST=${DST} -DSRC=${SRC}
        -DNAMESPACE=${NAMESPACE} -DKERNEL=${KERNEL}
        -P "${CMAKE_SOURCE_DIR}/cmake/scripts/preprocess_kernel.cmake"
        MAIN_DEPENDENCY ${SRC}
    )
endfunction(preprocess_opencl_kernel)

function(preprocess_opencl_kernels)
    set(out_dir ${ARGV0})
    set(namespace ${ARGV1})
    list(REMOVE_AT ARGV 0 1)

    foreach(kernel ${ARGV})
        get_filename_component(kernel_filename ${kernel} NAME)
        string(LENGTH ${kernel_filename} kernel_filename_length)
        math(EXPR kernel_filename_length "${kernel_filename_length} - 3")
        string(SUBSTRING ${kernel_filename} 0 ${kernel_filename_length} kernel_name)

        preprocess_opencl_kernel(${namespace} ${kernel_name}
            ${kernel}
            ${out_dir}/${kernel_name}_kernel.cpp
        )
    endforeach(kernel)
endfunction(preprocess_opencl_kernels)