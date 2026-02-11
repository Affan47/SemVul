serio_raw_write(struct file *file, const char __user *buffer,
			       size_t count, loff_t *ppos)
{
	struct serio_raw_client *client = file->private_data;
	struct serio_raw *serio_raw = client->serio_raw;
	int retval = 0;
	unsigned char c;

	retval = mutex_lock_interruptible(&serio_raw_mutex);
	if (retval)
		return retval;

	if (serio_raw->dead) {
		retval = -ENODEV;
		goto out;
	}

	if (count > 32)
		count = 32;

	while (count--) {
		if (get_user(c, buffer++)) {
			retval = -EFAULT;
			goto out;
		}

		if (serio_write(serio_raw->serio, c)) {

			if (retval == 0)
				retval = -EIO;
			goto out;
		}

		retval++;
	}

out:
	mutex_unlock(&serio_raw_mutex);
	return retval;
}
