start_shared(ompi_osc_sm_module_t *module,
             int target)
{
    uint32_t me = lk_fetch_add32(module, target,
                                 offsetof(ompi_osc_sm_lock_t, counter), 1);

    while (me != lk_fetch32(module, target,
                            offsetof(ompi_osc_sm_lock_t, read))) {
        opal_progress();
    }

    lk_add32(module, target, offsetof(ompi_osc_sm_lock_t, read), 1);

    return OMPI_SUCCESS;
}
