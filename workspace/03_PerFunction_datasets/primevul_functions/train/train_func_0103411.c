int lxc_unstack_mountpoint(const char *path, bool lazy)
{
	int ret;
	int umounts = 0;

pop_stack:
	ret = umount2(path, lazy ? MNT_DETACH : 0);
	if (ret < 0) {


		if (errno != EINVAL)
			return -errno;
	} else {


		if (umounts != INT_MAX)
			umounts++;


		goto pop_stack;
	}

	return umounts;
}
