as102_submit_urb_stream(struct as102_dev_t *dev, struct urb *urb)
{
	int err;

	usb_fill_bulk_urb(urb,
			  dev->bus_adap.usb_dev,
			  usb_rcvbulkpipe(dev->bus_adap.usb_dev, 0x2),
			  urb->transfer_buffer,
			  AS102_USB_BUF_SIZE,
			  as102_urb_stream_irq,
			  dev);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (err)
		dev_dbg(&urb->dev->dev,
			"%s: usb_submit_urb failed\n", __func__);

	return err;
}
