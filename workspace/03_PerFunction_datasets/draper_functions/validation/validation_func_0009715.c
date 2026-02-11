dc1394_avt_get_channel_adjust(dc1394camera_t *camera, int16_t *channel_adjust)
{
    dc1394error_t err;
    uint32_t value;


    err=dc1394_get_adv_control_register(camera,REG_CAMERA_AVT_CHANNEL_ADJUST_VALUE, &value);
    DC1394_ERR_RTN(err,"Could not get AVT channel adjust");


    *channel_adjust = (int16_t)value;

    return DC1394_SUCCESS;
}
