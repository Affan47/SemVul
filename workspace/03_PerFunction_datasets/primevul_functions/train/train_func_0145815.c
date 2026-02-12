static void __exit af9005_usb_module_exit(void)
{

	if (rc_decode != NULL)
		symbol_put(af9005_rc_decode);
	if (rc_keys != NULL)
		symbol_put(rc_map_af9005_table);
	if (rc_keys_size != NULL)
		symbol_put(rc_map_af9005_table_size);

	usb_deregister(&af9005_usb_driver);
}
