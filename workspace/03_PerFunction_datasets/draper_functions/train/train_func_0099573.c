clist_init_states(gx_device * dev, byte * init_data, uint data_size)
{
    gx_device_clist_writer * const cdev =
        &((gx_device_clist *)dev)->writer;
    ulong state_size = cdev->nbands * (ulong) sizeof(gx_clist_state);

    long alignment = (-(long)init_data) & (sizeof(init_data) - 1);


    if (state_size + sizeof(cmd_prefix) + cmd_largest_size + 100 + alignment > data_size)
        return_error(gs_error_rangecheck);

    cdev->cend = init_data + data_size;
    init_data +=  alignment;
    cdev->states = (gx_clist_state *) init_data;
    cdev->cbuf = init_data + state_size;
    return 0;
}
