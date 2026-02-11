rt2800usb_autorun_detect(struct rt2x00_dev *rt2x00dev)
{
	__le32 *reg;
	u32 fw_mode;
	int ret;

	reg = kmalloc(sizeof(*reg), GFP_KERNEL);
	if (reg == NULL)
		return -ENOMEM;


	ret = rt2x00usb_vendor_request(rt2x00dev, USB_DEVICE_MODE,
				       USB_VENDOR_REQUEST_IN, 0,
				       USB_MODE_AUTORUN, reg, sizeof(*reg),
				       REGISTER_TIMEOUT_FIRMWARE);
	fw_mode = le32_to_cpu(*reg);
	kfree(reg);
	if (ret < 0)
		return ret;

	if ((fw_mode & 0x00000003) == 2)
		return 1;

	return 0;
}
