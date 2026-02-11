vprbrd_i2c_receive(struct usb_device *usb_dev,
	struct vprbrd_i2c_read_msg *rmsg, int bytes_xfer)
{
	int ret, bytes_actual;
	int error = 0;


	ret = usb_bulk_msg(usb_dev,
		usb_sndbulkpipe(usb_dev, VPRBRD_EP_OUT), rmsg,
		sizeof(struct vprbrd_i2c_read_hdr), &bytes_actual,
		VPRBRD_USB_TIMEOUT_MS);

	if ((ret < 0)
		|| (bytes_actual != sizeof(struct vprbrd_i2c_read_hdr))) {
		dev_err(&usb_dev->dev, "failure transmitting usb\n");
		error = -EREMOTEIO;
	}


	ret = usb_bulk_msg(usb_dev,
		usb_rcvbulkpipe(usb_dev, VPRBRD_EP_IN), rmsg,
		bytes_xfer, &bytes_actual, VPRBRD_USB_TIMEOUT_MS);

	if ((ret < 0) || (bytes_xfer != bytes_actual)) {
		dev_err(&usb_dev->dev, "failure receiving usb\n");
		error = -EREMOTEIO;
	}
	return error;
}
