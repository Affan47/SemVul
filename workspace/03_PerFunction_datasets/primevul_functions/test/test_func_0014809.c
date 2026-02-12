static void em28xx_release_resources(struct em28xx *dev)
{
	struct usb_device *udev = interface_to_usbdev(dev->intf);


	mutex_lock(&dev->lock);

	em28xx_unregister_media_device(dev);

	if (dev->def_i2c_bus)
		em28xx_i2c_unregister(dev, 1);
	em28xx_i2c_unregister(dev, 0);

	if (dev->ts == PRIMARY_TS)
		usb_put_dev(udev);


	clear_bit(dev->devno, em28xx_devused);

	mutex_unlock(&dev->lock);
};
