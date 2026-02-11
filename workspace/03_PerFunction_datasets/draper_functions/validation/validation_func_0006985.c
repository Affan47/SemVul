cpl_memory_init(int mode)
{
    if (cpl_memory_mode < 0) {
        if (mode == 0) {
            static const cx_memory_vtable cpl_memory_services_system = {
                (cxptr(*)(cxsize))malloc,
                (cxptr (*)(cxsize, cxsize))calloc,
                (cxptr (*) (cxptr, cxsize))realloc,
                (void (*) (cxptr))free
            };
            cx_memory_vtable_set(&cpl_memory_services_system);
            cpl_memory_mode = 0;
#ifndef _OPENMP

        } else if (mode == 2) {
            static const cx_memory_vtable cpl_memory_services_xmemory = {
                (cxptr(*)(cxsize))cpl_xmemory_malloc,
                (cxptr (*)(cxsize, cxsize))cpl_xmemory_calloc,
                (cxptr (*) (cxptr, cxsize))cpl_xmemory_realloc,
                (void (*) (cxptr))cpl_xmemory_free
            };
            cx_memory_vtable_set(&cpl_memory_services_xmemory);
            cpl_memory_mode = 2;
#endif
        } else {
            static const cx_memory_vtable cpl_memory_services_count = {
                (cxptr(*)(cxsize))cpl_xmemory_malloc_count,
                (cxptr (*)(cxsize, cxsize))cpl_xmemory_calloc_count,
                (cxptr (*) (cxptr, cxsize))cpl_xmemory_realloc_count,
                (void (*) (cxptr))cpl_xmemory_free_count
            };
            cx_memory_vtable_set(&cpl_memory_services_count);
            cpl_memory_mode = 1;
        }
    }

    return;
}
