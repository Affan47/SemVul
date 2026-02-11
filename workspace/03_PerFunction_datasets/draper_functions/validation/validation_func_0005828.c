bulk_immediate(struct usb_serial_port *port, u8 *buf, u8 count)
{
	int status;
	struct usb_serial *serial = port->serial;
	int actual = 0;


	status =
	    usb_bulk_msg(serial->dev,
			 usb_sndbulkpipe(serial->dev,
					 port->bulk_out_endpointAddress), buf,
			 count, &actual, 1000);

	if (status != IUU_OPERATION_OK)
		dev_dbg(&port->dev, "%s - error = %2x\n", __func__, status);
	else
		dev_dbg(&port->dev, "%s - write OK !\n", __func__);
	return status;
}
