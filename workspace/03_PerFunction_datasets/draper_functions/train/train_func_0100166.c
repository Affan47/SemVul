f2fs_dev_is_umounted(struct f2fs_configuration *c)
{
	struct stat st_buf;
	int ret = 0;

	ret = is_mounted(MOUNTED, c->device_name);
	if (ret) {
		MSG(0, "\tError: Not available on mounted device!\n");
		return -1;
	}


	ret = is_mounted("/proc/mounts", c->device_name);
	if (ret) {
		MSG(0, "\tError: Not available on mounted device!\n");
		return -1;
	}


	if (stat(c->device_name, &st_buf) == 0 && S_ISBLK(st_buf.st_mode)) {
		int fd = open(c->device_name, O_RDONLY | O_EXCL);

		if (fd >= 0) {
			close(fd);
		} else if (errno == EBUSY) {
			MSG(0, "\tError: In use by the system!\n");
			return -1;
		}
	}
	return 0;
}
