fd_close(int *fd_ptr)
{
	int ret, fd;

	g_assert(NULL != fd_ptr);

	fd = *fd_ptr;
	g_assert(fd >= -1);

	if (fd < 0) {
		ret = 0;
	} else {
		ret = close(fd);
		*fd_ptr = -1;
	}
	return ret;
}
