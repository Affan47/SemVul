gx_default_put_blackpreserve(gsicc_blackpreserve_t blackpreserve, gx_device * dev,
                           gsicc_profile_types_t index)
{
    int code;
    cmm_dev_profile_t *profile_struct;

    if (dev->procs.get_profile == NULL) {


        if (dev->icc_struct == NULL) {

            dev->icc_struct = gsicc_new_device_profile_array(dev->memory);
            if (dev->icc_struct == NULL)
                return_error(gs_error_VMerror);
        }
        code = gsicc_set_device_blackpreserve(dev, blackpreserve, index);
    } else {
        code = dev_proc(dev, get_profile)(dev,  &profile_struct);
        if (code < 0)
            return code;
        if (profile_struct == NULL) {

            dev->icc_struct = gsicc_new_device_profile_array(dev->memory);
            if (dev->icc_struct == NULL)
                return_error(gs_error_VMerror);
        }
        code = gsicc_set_device_blackpreserve(dev, blackpreserve, index);
    }
    return code;
}
