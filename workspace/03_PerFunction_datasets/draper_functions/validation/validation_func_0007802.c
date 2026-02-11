tool_dbfn_read(struct tool_ctx *tc, char __user *ubuf,
			      size_t size, loff_t *offp,
			      u64 (*db_read_fn)(struct ntb_dev *))
{
	size_t buf_size;
	char *buf;
	ssize_t pos, rc;

	if (!db_read_fn)
		return -EINVAL;

	buf_size = min_t(size_t, size, 0x20);

	buf = kmalloc(buf_size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	pos = scnprintf(buf, buf_size, "%#llx\n",
			db_read_fn(tc->ntb));

	rc = simple_read_from_buffer(ubuf, size, offp, buf, pos);

	kfree(buf);

	return rc;
}
