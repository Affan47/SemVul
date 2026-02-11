check_loop_mounted(const char *mnt_fsname, dev_t mnt_rdev,
				dev_t file_dev, ino_t file_ino)
{
#if defined(HAVE_LINUX_LOOP_H) && defined(HAVE_LINUX_MAJOR_H)
	struct loop_info64 loopinfo;
	int loop_fd, ret;

	if (major(mnt_rdev) == LOOP_MAJOR) {
		loop_fd = open(mnt_fsname, O_RDONLY);
		if (loop_fd < 0)
			return -1;

		ret = ioctl(loop_fd, LOOP_GET_STATUS64, &loopinfo);
		close(loop_fd);
		if (ret < 0)
			return -1;

		if (file_dev == loopinfo.lo_device &&
				file_ino == loopinfo.lo_inode)
			return 1;
	}
#endif
	return 0;
}
