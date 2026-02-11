closePort()
{
#ifdef WIN32
    switch (usbMode) {
    case USB2 :
        usb2->close();
        return 0;
        break;
    case USB1 :
        return (int)!CloseHandle(devicePort);
        break;
    default :
        return -1;
        break;
    }
#else

#ifdef GC_HAVE_LIBUSB
    if (usbMode == USB2) {
        usb2->close();
        return 0;
    }
#endif
    tcflush(devicePort, TCIOFLUSH);
    return close(devicePort);
#endif
}
