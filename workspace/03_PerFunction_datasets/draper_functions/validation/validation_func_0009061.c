read_file(struct nandsim *ns, struct file *file, void *buf, size_t count, loff_t pos)
{
	ssize_t tx;
	int err, memalloc;

	err = get_pages(ns, file, count, pos);
	if (err)
		return err;
	memalloc = set_memalloc();
	tx = kernel_read(file, pos, buf, count);
	clear_memalloc(memalloc);
	put_pages(ns);
	return tx;
}
