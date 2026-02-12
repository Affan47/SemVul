static void __exit usbip_host_exit(void)
{
	driver_remove_file(&stub_driver.drvwrap.driver,
			   &driver_attr_match_busid);

	driver_remove_file(&stub_driver.drvwrap.driver,
			   &driver_attr_rebind);


	usb_deregister_device_driver(&stub_driver);


	stub_device_rebind();

	kmem_cache_destroy(stub_priv_cache);
}
