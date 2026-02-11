pcipcwd_temp_open(struct inode *inode, struct file *file)
{
	if (!pcipcwd_private.supports_temp)
		return -ENODEV;

	return nonseekable_open(inode, file);
}
