ufx_reg_write(struct ufx_data *dev, u32 index, u32 data)
{
	u32 *buf = kmalloc(4, GFP_KERNEL);
	int ret;

	BUG_ON(!dev);

	if (!buf)
		return -ENOMEM;

	*buf = data;
	cpu_to_le32s(buf);

	ret = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
		USB_VENDOR_REQUEST_WRITE_REGISTER,
		USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		00, index, buf, 4, USB_CTRL_SET_TIMEOUT);

	kfree(buf);

	if (unlikely(ret < 0))
		pr_warn("Failed to write register index 0x%08x with value "
			"0x%08x\n", index, data);

	return ret;
}
