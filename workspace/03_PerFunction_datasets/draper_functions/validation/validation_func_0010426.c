lcd_write(struct file *file,
			 const char __user *buf, size_t count, loff_t *ppos)
{
	const char __user *tmp = buf;
	char c;

	for (; count-- > 0; (*ppos)++, tmp++) {
		if (!in_interrupt() && (((count + 1) & 0x1f) == 0))


			schedule();

		if (get_user(c, tmp))
			return -EFAULT;

		lcd_write_char(c);
	}

	return tmp - buf;
}
