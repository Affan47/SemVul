bsd_get_bootstrap(struct fdisk_context *cxt,
			char *path, void *ptr, int size)
{
	int fd;

	if ((fd = open(path, O_RDONLY)) < 0) {
		fdisk_warn(cxt, _("cannot open %s"), path);
		return -errno;
	}

	if (read_all(fd, ptr, size) != size) {
		fdisk_warn(cxt, _("cannot read %s"), path);
		close(fd);
		return -errno;
	}

	fdisk_info(cxt, _("The bootstrap file %s successfully loaded."), path);
	close (fd);
	return 0;
}
