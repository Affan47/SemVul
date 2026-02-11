il_dbgfs_force_reset_write(struct file *file, const char __user *user_buf,
			   size_t count, loff_t *ppos)
{

	int ret;
	struct il_priv *il = file->private_data;

	ret = il_force_reset(il, true);

	return ret ? ret : count;
}
