void* leak_memalign(size_t alignment, size_t bytes)
{

    if (alignment <= MALLOC_ALIGNMENT)
        return leak_malloc(bytes);


    if (alignment & (alignment-1))
        alignment = 1L << (31 - __builtin_clz(alignment));


    size_t size = (alignment-MALLOC_ALIGNMENT) + bytes;
    if (size < bytes) {
        return NULL;
    }

    void* base = leak_malloc(size);
    if (base != NULL) {
        intptr_t ptr = (intptr_t)base;
        if ((ptr % alignment) == 0)
            return base;


        ptr += ((-ptr) % alignment);


        ((void**)ptr)[-1] = MEMALIGN_GUARD;
        ((void**)ptr)[-2] = base;

        return (void*)ptr;
    }
    return base;
}
