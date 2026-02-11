gx_default_put_graydetection(bool graydetection, gx_device * dev)
{
    int code = 0;
    cmm_dev_profile_t *profile_struct;

    if (dev->procs.get_profile == NULL) {


        if (dev->icc_struct == NULL) {

            dev->icc_struct = gsicc_new_device_profile_array(dev->memory);
        }
        dev->icc_struct->graydetection = graydetection;
        dev->icc_struct->pageneutralcolor = graydetection;
    } else {
        code = dev_proc(dev, get_profile)(dev,  &profile_struct);
        if (profile_struct == NULL) {

            dev->icc_struct = gsicc_new_device_profile_array(dev->memory);
            profile_struct =  dev->icc_struct;
        }
        profile_struct->graydetection = graydetection;
        profile_struct->pageneutralcolor = graydetection;
    }
    return code;
}
