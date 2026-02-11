cx231xx_ep5_bulkout(struct cx231xx *dev, u8 *firmware, u16 size)
{
	int errCode = 0;
	int actlen, ret = -ENOMEM;
	u32 *buffer;

	buffer = kzalloc(4096, GFP_KERNEL);
	if (buffer == NULL)
		return -ENOMEM;
	memcpy(&buffer[0], firmware, 4096);

	ret = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, 5),
			buffer, 4096, &actlen, 2000);

	if (ret)
		dev_err(dev->dev,
			"bulk message failed: %d (%d/%d)", ret,
			size, actlen);
	else {
		errCode = actlen != size ? -1 : 0;
	}
	kfree(buffer);
	return errCode;
}
