kernel void add(global int* a, global int* b, global int* c) {
    unsigned int i = get_global_id(0);

    c[i] = a[i] + b[i];
}

kernel void gid(global unsigned int* xs) {
    unsigned int i = get_global_id(0);

    if (id() < 1024) {
        xs[i] = i;
    }
}