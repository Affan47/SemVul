static void usbvision_disconnect(struct usb_interface *intf)
{
	struct usb_usbvision *usbvision = to_usbvision(usb_get_intfdata(intf));

	PDEBUG(DBG_PROBE, "");

	if (usbvision == NULL) {
		pr_err("%s: usb_get_intfdata() failed\n", __func__);
		return;
	}

	mutex_lock(&usbvision->v4l2_lock);


	usbvision_stop_isoc(usbvision);

	v4l2_device_disconnect(&usbvision->v4l2_dev);
	usbvision_i2c_unregister(usbvision);
	usbvision->remove_pending = 1;

	usb_put_dev(usbvision->dev);
	usbvision->dev = NULL;

	mutex_unlock(&usbvision->v4l2_lock);

	if (usbvision->user) {
		printk(KERN_INFO "%s: In use, disconnect pending\n",
		       __func__);
		wake_up_interruptible(&usbvision->wait_frame);
		wake_up_interruptible(&usbvision->wait_stream);
	} else {
		usbvision_release(usbvision);
	}

	PDEBUG(DBG_PROBE, "success");
}
