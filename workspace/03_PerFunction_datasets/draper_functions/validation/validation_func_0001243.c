selinux_transaction_write(struct file *file, const char __user *buf, size_t size, loff_t *pos)
{
	ino_t ino = file_inode(file)->i_ino;
	char *data;
	ssize_t rv;

	if (ino >= ARRAY_SIZE(write_op) || !write_op[ino])
		return -EINVAL;

	data = simple_transaction_get(file, buf, size);
	if (IS_ERR(data))
		return PTR_ERR(data);

	rv = write_op[ino](file, data, size);
	if (rv > 0) {
		simple_transaction_set(file, rv);
		rv = size;
	}
	return rv;
}
