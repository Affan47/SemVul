_memheap_create(void)
{
    int rc = OSHMEM_SUCCESS;
    static memheap_context_t context;
    size_t user_size;

    user_size = _memheap_size();
    if (user_size < MEMHEAP_BASE_MIN_SIZE) {
        MEMHEAP_ERROR("Requested memheap size is less than minimal meamheap size (%llu < %llu)",
                      (unsigned long long)user_size, MEMHEAP_BASE_MIN_SIZE);
        return NULL ;
    }

    if (OSHMEM_SUCCESS == rc) {
        rc = mca_memheap_base_alloc_init(&mca_memheap_base_map,
                                         user_size + MEMHEAP_BASE_PRIVATE_SIZE);
    }


    if (OSHMEM_SUCCESS == rc) {
        rc = mca_memheap_base_static_init(&mca_memheap_base_map);
    }


    if (OSHMEM_SUCCESS == rc) {
        rc = mca_memheap_base_reg(&mca_memheap_base_map);
    }


    if (OSHMEM_SUCCESS == rc) {
        rc = memheap_oob_init(&mca_memheap_base_map);
    }

    if (OSHMEM_SUCCESS == rc) {
        context.user_size = user_size;
        context.private_size = MEMHEAP_BASE_PRIVATE_SIZE;
        context.user_base_addr =
                (void*) ((unsigned char*) mca_memheap_base_map.mem_segs[HEAP_SEG_INDEX].seg_base_addr
                        + 0);
        context.private_base_addr =
                (void*) ((unsigned char*) mca_memheap_base_map.mem_segs[HEAP_SEG_INDEX].seg_base_addr
                        + context.user_size);
    }

    return ((OSHMEM_SUCCESS == rc) ? &context : NULL );
}
