driver_get_axis_info( CoreInputDevice              *device,
                      void                         *driver_data,
                      DFBInputDeviceAxisIdentifier  axis,
                      DFBInputDeviceAxisInfo       *ret_info )
{
     LinuxInputData *data = (LinuxInputData*) driver_data;

     if (data->touchpad)
          return DFB_OK;

     if (axis <= ABS_PRESSURE && axis < DIAI_LAST) {
          unsigned long absbit[NBITS(ABS_CNT)];


          ioctl( data->fd, EVIOCGBIT(EV_ABS, sizeof(absbit)), absbit );

          if (test_bit (axis, absbit)) {
               struct input_absinfo absinfo;

               if (ioctl( data->fd, EVIOCGABS(axis), &absinfo ) == 0 &&
                   (absinfo.minimum || absinfo.maximum)) {
                    ret_info->flags  |= DIAIF_ABS_MIN | DIAIF_ABS_MAX;
                    ret_info->abs_min = absinfo.minimum;
                    ret_info->abs_max = absinfo.maximum;
               }
          }
     }

     return DFB_OK;
}
