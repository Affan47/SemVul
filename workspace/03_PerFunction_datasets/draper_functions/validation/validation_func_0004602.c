mwifiex_debug_read(struct file *file, char __user *ubuf,
		   size_t count, loff_t *ppos)
{
	struct mwifiex_private *priv =
		(struct mwifiex_private *) file->private_data;
	unsigned long page = get_zeroed_page(GFP_KERNEL);
	char *p = (char *) page;
	ssize_t ret;

	if (!p)
		return -ENOMEM;

	ret = mwifiex_get_debug_info(priv, &info);
	if (ret)
		goto free_and_exit;

	p += mwifiex_debug_info_to_buffer(priv, p, &info);

	ret = simple_read_from_buffer(ubuf, count, ppos, (char *) page,
				      (unsigned long) p - page);

free_and_exit:
	free_page(page);
	return ret;
}
