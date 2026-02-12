static void adu_disconnect(struct usb_interface *interface)
{
	struct adu_device *dev;

	dev = usb_get_intfdata(interface);

	usb_deregister_dev(interface, &adu_class);

	mutex_lock(&adutux_mutex);
	usb_set_intfdata(interface, NULL);

	mutex_lock(&dev->mtx);
	dev->udev = NULL;
	mutex_unlock(&dev->mtx);


	if (!dev->open_count)
		adu_delete(dev);

	mutex_unlock(&adutux_mutex);
}
