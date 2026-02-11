attach_and_init(opal_shmem_ds_t *shmem_bufp,
                size_t size,
                size_t size_ctl_structure,
                size_t data_seg_alignment,
                bool first_call)
{
    mca_common_sm_module_t *map = NULL;
    mca_common_sm_seg_header_t *seg = NULL;
    unsigned char *addr = NULL;


    if (NULL == (seg = (mca_common_sm_seg_header_t *)
                       opal_shmem_segment_attach(shmem_bufp))) {
        return NULL;
    }
    opal_atomic_rmb();

    if (NULL == (map = OBJ_NEW(mca_common_sm_module_t))) {
        OMPI_ERROR_LOG(OMPI_ERR_OUT_OF_RESOURCE);
        (void)opal_shmem_segment_detach(shmem_bufp);
        return NULL;
    }


    if (OPAL_SUCCESS != opal_shmem_ds_copy(shmem_bufp, &map->shmem_ds)) {
        (void)opal_shmem_segment_detach(shmem_bufp);
        free(map);
        return NULL;
    }


    map->module_seg = seg;

    addr = ((unsigned char *)seg) + size_ctl_structure;


    if (0 != data_seg_alignment) {
        addr = OPAL_ALIGN_PTR(addr, data_seg_alignment, unsigned char *);

        if ((unsigned char *)seg + shmem_bufp->seg_size < addr) {
            opal_show_help("help-mpi-common-sm.txt", "mmap too small", 1,
                           ompi_process_info.nodename,
                           (unsigned long)shmem_bufp->seg_size,
                           (unsigned long)size_ctl_structure,
                           (unsigned long)data_seg_alignment);
            (void)opal_shmem_segment_detach(shmem_bufp);
            free(map);
            return NULL;
        }
    }

    map->module_data_addr = addr;
    map->module_seg_addr = (unsigned char *)seg;


    if (first_call) {

        size_t mem_offset = map->module_data_addr -
                            (unsigned char *)map->module_seg;
        opal_atomic_init(&map->module_seg->seg_lock, OPAL_ATOMIC_UNLOCKED);
        map->module_seg->seg_inited = 0;
        map->module_seg->seg_num_procs_inited = 0;
        map->module_seg->seg_offset = mem_offset;
        map->module_seg->seg_size = size - mem_offset;
        opal_atomic_wmb();
    }


    (void)opal_atomic_add_size_t(&map->module_seg->seg_num_procs_inited, 1);


    opal_atomic_wmb();

    return map;
}
