static void __exit hso_exit(void)
{
	pr_info("unloaded\n");

	tty_unregister_driver(tty_drv);

	usb_deregister(&hso_driver);
	put_tty_driver(tty_drv);
}
