static int __init usbvision_init(void)
{
	int err_code;

	PDEBUG(DBG_PROBE, "");

	PDEBUG(DBG_IO,  "IO      debugging is enabled [video]");
	PDEBUG(DBG_PROBE, "PROBE   debugging is enabled [video]");
	PDEBUG(DBG_MMAP, "MMAP    debugging is enabled [video]");


	if (isoc_mode != ISOC_MODE_COMPRESS) {

		usbvision_v4l2_format[6].supported = 0;
		usbvision_v4l2_format[7].supported = 0;
	}

	err_code = usb_register(&usbvision_driver);

	if (err_code == 0) {
		printk(KERN_INFO DRIVER_DESC " : " USBVISION_VERSION_STRING "\n");
		PDEBUG(DBG_PROBE, "success");
	}
	return err_code;
}
