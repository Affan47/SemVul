bulk_w(struct gspca_dev *gspca_dev,
		  u8 tag,
		  const u8 *data,
		  int length)
{
	struct usb_device *dev = gspca_dev->dev;
	int count, actual_count, ret;

	if (gspca_dev->usb_err < 0)
		return;
	for (;;) {
		count = length > BULK_OUT_SIZE - 1
				? BULK_OUT_SIZE - 1 : length;
		gspca_dev->usb_buf[0] = tag;
		memcpy(&gspca_dev->usb_buf[1], data, count);
		ret = usb_bulk_msg(dev,
				   usb_sndbulkpipe(dev, 3),
				   gspca_dev->usb_buf, count + 1,
				   &actual_count, 500);
		if (ret < 0) {
			pr_err("bulk write error %d tag=%02x\n",
				ret, tag);
			gspca_dev->usb_err = ret;
			return;
		}
		length -= count;
		if (length <= 0)
			break;
		data += count;
	}
}
