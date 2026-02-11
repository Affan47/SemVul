m920x_read(struct usb_device *udev, u8 request, u16 value,
			     u16 index, void *data, int size)
{
	int ret;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      request, USB_TYPE_VENDOR | USB_DIR_IN,
			      value, index, data, size, 2000);
	if (ret < 0) {
		printk(KERN_INFO "m920x_read = error: %d\n", ret);
		return ret;
	}

	if (ret != size) {
		deb("m920x_read = no data\n");
		return -EIO;
	}

	return 0;
}
