usb_driver_release_interface(struct usb_driver *driver,
					struct usb_interface *iface)
{
	struct device *dev = &iface->dev;


	if (!dev->driver || dev->driver != &driver->drvwrap.driver)
		return;


	if (iface->condition != USB_INTERFACE_BOUND)
		return;
	iface->condition = USB_INTERFACE_UNBINDING;


	if (device_is_registered(dev)) {
		device_release_driver(dev);
	} else {
		device_lock(dev);
		usb_unbind_interface(dev);
		dev->driver = NULL;
		device_unlock(dev);
	}
}
