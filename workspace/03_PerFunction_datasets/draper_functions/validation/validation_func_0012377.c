reg_w(struct gspca_dev *gspca_dev,
			u16 value, u16 index)
{
	struct usb_device *dev = gspca_dev->dev;
	int ret;

	if (gspca_dev->usb_err < 0)
		return;
	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			0x02,
			USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			value,
			index,
			NULL,
			0,
			500);
	if (ret < 0) {
		pr_err("reg_w err %d\n", ret);
		gspca_dev->usb_err = ret;
	}
}
