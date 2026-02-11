g15NumberOfConnectedDevices() {
    struct usb_bus *bus = 0;
    struct usb_device *dev = 0;
    int i=0;
    unsigned int found = 0;

    for (i=0; g15_devices[i].name !=NULL;i++)
        for (bus = usb_busses; bus; bus = bus->next)
    {
        for (dev = bus->devices; dev; dev = dev->next)
        {
            if ((dev->descriptor.idVendor == g15_devices[i].vendorid && dev->descriptor.idProduct == g15_devices[i].productid))
                found++;
        }
    }
    g15_log(stderr,G15_LOG_INFO,"Found %i supported devices\n",found);
    return found;
}
