sysfs_readlink(struct sysfs_cxt *cxt, const char *attr,
		   char *buf, size_t bufsiz)
{
	if (attr)
		return readlink_at(cxt->dir_fd, cxt->dir_path, attr, buf, bufsiz);


	return readlink(cxt->dir_path, buf, bufsiz);
}
