static int __init sixpack_init_driver(void)
{
	int status;

	printk(msg_banner);


	status = tty_register_ldisc(&sp_ldisc);
	if (status)
		printk(msg_regfail, status);

	return status;
}
