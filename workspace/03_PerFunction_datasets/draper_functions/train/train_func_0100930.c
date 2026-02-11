at76_mod_init(void)
{
	int result;

	printk(KERN_INFO DRIVER_DESC " " DRIVER_VERSION " loading\n");

	mutex_init(&fw_mutex);


	result = usb_register(&at76_driver);
	if (result < 0)
		printk(KERN_ERR DRIVER_NAME
		       ": usb_register failed (status %d)\n", result);

	led_trigger_register_simple("at76_usb-tx", &ledtrig_tx);
	return result;
}
