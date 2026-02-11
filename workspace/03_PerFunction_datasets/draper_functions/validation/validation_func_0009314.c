codec_reg_read_file(struct file *file, char __user *user_buf,
				   size_t count, loff_t *ppos)
{
	ssize_t ret;
	struct snd_soc_codec *codec = file->private_data;
	char *buf;

	if (*ppos < 0 || !count)
		return -EINVAL;

	buf = kmalloc(count, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	ret = soc_codec_reg_show(codec, buf, count, *ppos);
	if (ret >= 0) {
		if (copy_to_user(user_buf, buf, ret)) {
			kfree(buf);
			return -EFAULT;
		}
		*ppos += ret;
	}

	kfree(buf);
	return ret;
}
