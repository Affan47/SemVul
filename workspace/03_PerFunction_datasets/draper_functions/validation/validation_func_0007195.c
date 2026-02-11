cp210x_set_config(struct usb_serial_port *port, u8 request,
		unsigned int *data, int size)
{
	struct usb_serial *serial = port->serial;
	struct cp210x_serial_private *spriv = usb_get_serial_data(serial);
	__le32 *buf;
	int result, i, length;


	length = (((size - 1) | 3) + 1) / 4;

	buf = kmalloc(length * sizeof(__le32), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;


	for (i = 0; i < length; i++)
		buf[i] = cpu_to_le32(data[i]);

	if (size > 2) {
		result = usb_control_msg(serial->dev,
				usb_sndctrlpipe(serial->dev, 0),
				request, REQTYPE_HOST_TO_INTERFACE, 0x0000,
				spriv->bInterfaceNumber, buf, size,
				USB_CTRL_SET_TIMEOUT);
	} else {
		result = usb_control_msg(serial->dev,
				usb_sndctrlpipe(serial->dev, 0),
				request, REQTYPE_HOST_TO_INTERFACE, data[0],
				spriv->bInterfaceNumber, NULL, 0,
				USB_CTRL_SET_TIMEOUT);
	}

	kfree(buf);

	if ((size > 2 && result != size) || result < 0) {
		dev_dbg(&port->dev, "%s - Unable to send request, request=0x%x size=%d result=%d\n",
			__func__, request, size, result);
		if (result > 0)
			result = -EPROTO;

		return result;
	}

	return 0;
}
