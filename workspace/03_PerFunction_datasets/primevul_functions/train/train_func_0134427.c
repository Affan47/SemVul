static int __init hso_init(void)
{
	int i;
	int result;


	pr_info("%s\n", version);


	spin_lock_init(&serial_table_lock);
	for (i = 0; i < HSO_SERIAL_TTY_MINORS; i++)
		serial_table[i] = NULL;


	tty_drv = alloc_tty_driver(HSO_SERIAL_TTY_MINORS);
	if (!tty_drv)
		return -ENOMEM;


	tty_drv->driver_name = driver_name;
	tty_drv->name = tty_filename;


	if (tty_major)
		tty_drv->major = tty_major;

	tty_drv->minor_start = 0;
	tty_drv->type = TTY_DRIVER_TYPE_SERIAL;
	tty_drv->subtype = SERIAL_TYPE_NORMAL;
	tty_drv->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	tty_drv->init_termios = tty_std_termios;
	hso_init_termios(&tty_drv->init_termios);
	tty_set_operations(tty_drv, &hso_serial_ops);


	result = tty_register_driver(tty_drv);
	if (result) {
		pr_err("%s - tty_register_driver failed(%d)\n",
		       __func__, result);
		goto err_free_tty;
	}


	result = usb_register(&hso_driver);
	if (result) {
		pr_err("Could not register hso driver - error: %d\n", result);
		goto err_unreg_tty;
	}


	return 0;
err_unreg_tty:
	tty_unregister_driver(tty_drv);
err_free_tty:
	put_tty_driver(tty_drv);
	return result;
}
