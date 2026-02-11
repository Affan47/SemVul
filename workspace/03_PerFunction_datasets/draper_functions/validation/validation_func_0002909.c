OpenAntStick()
{
    struct usb_bus* bus;
    struct usb_device* dev;
    struct usb_dev_handle* udev;


#ifndef WIN32
    for (bus = usb_get_busses(); bus; bus = bus->next) {

        for (dev = bus->devices; dev; dev = dev->next) {

            if (dev->descriptor.idVendor == GARMIN_USB2_VID &&
                (dev->descriptor.idProduct == GARMIN_USB2_PID || dev->descriptor.idProduct == GARMIN_OEM_PID)) {

                if ((udev = usb_open(dev))) {
                    usb_reset(udev);
                    usb_close(udev);
                }
            }
        }
    }
#endif

    for (bus = usb_get_busses(); bus; bus = bus->next) {

        for (dev = bus->devices; dev; dev = dev->next) {

            if (dev->descriptor.idVendor == GARMIN_USB2_VID &&
                (dev->descriptor.idProduct == GARMIN_USB2_PID || dev->descriptor.idProduct == GARMIN_OEM_PID)) {


                if ((udev = usb_open(dev))) {

                    if (dev->descriptor.bNumConfigurations) {

                        if ((intf = usb_find_interface(&dev->config[0])) != NULL) {

#ifdef Q_OS_LINUX
                            usb_detach_kernel_driver_np(udev, interface);
#endif

                            int rc = usb_set_configuration(udev, 1);
                            if (rc < 0) {
                                qDebug()<<"usb_set_configuration Error: "<< usb_strerror();
                                if (OperatingSystem == LINUX) {

                                    qDebug()<<"check permissions on:"<<QString("/dev/bus/usb/%1/%2").arg(bus->dirname).arg(dev->filename);
                                    qDebug()<<"did you remember to setup a udev rule for this device?";
                                }
                            }

                            rc = usb_claim_interface(udev, interface);
                            if (rc < 0) qDebug()<<"usb_claim_interface Error: "<< usb_strerror();

                            if (OperatingSystem != OSX) {

                                rc = usb_set_altinterface(udev, alternate);
                                if (rc < 0) qDebug()<<"usb_set_altinterface Error: "<< usb_strerror();
                            }

                            return udev;
                        }
                    }

                    usb_close(udev);
                }
            }
        }
    }
    return NULL;
}
