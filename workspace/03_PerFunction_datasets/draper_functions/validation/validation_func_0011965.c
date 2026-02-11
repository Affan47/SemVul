il_dbgfs_sram_write(struct file *file, const char __user *user_buf,
		    size_t count, loff_t *ppos)
{
	struct il_priv *il = file->private_data;
	char buf[64];
	int buf_size;
	u32 offset, len;

	memset(buf, 0, sizeof(buf));
	buf_size = min(count, sizeof(buf) - 1);
	if (copy_from_user(buf, user_buf, buf_size))
		return -EFAULT;

	if (sscanf(buf, "%x,%x", &offset, &len) == 2) {
		il->dbgfs_sram_offset = offset;
		il->dbgfs_sram_len = len;
	} else {
		il->dbgfs_sram_offset = 0;
		il->dbgfs_sram_len = 0;
	}

	return count;
}
