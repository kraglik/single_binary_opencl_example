__kernel void add(__global int* a, __global int* b, __global int* c) {
    unsigned int i = get_global_id(0);

    c[i] = a[i] + b[i];
}

__kernel void gid(__global unsigned int* xs) {
    unsigned int i = get_global_id(0);

    if (i < 1024) {
        xs[i] = i;
    }
}