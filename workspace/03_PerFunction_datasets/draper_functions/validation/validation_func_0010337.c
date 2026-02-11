mgsl_hangup(struct tty_struct *tty)
{
	struct mgsl_struct * info = tty->driver_data;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_hangup(%s)\n",
			 __FILE__,__LINE__, info->device_name );

	if (mgsl_paranoia_check(info, tty->name, "mgsl_hangup"))
		return;

	mgsl_flush_buffer(tty);
	shutdown(info);

	info->port.count = 0;
	info->port.flags &= ~ASYNC_NORMAL_ACTIVE;
	info->port.tty = NULL;

	wake_up_interruptible(&info->port.open_wait);

}
