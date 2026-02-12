int sys_posix_fallocate(int fd, off_t offset, off_t len)
{
#if defined(HAVE_POSIX_FALLOCATE) && !defined(HAVE_BROKEN_POSIX_FALLOCATE)
	return posix_fallocate(fd, offset, len);
#elif defined(F_RESVSP64)

	struct flock64 fl;
	off_t new_len = offset + len;
	int ret;
	struct stat64 sbuf;


	if (new_len < 0)
		return EFBIG;

	fl.l_whence = SEEK_SET;
	fl.l_start = offset;
	fl.l_len = len;

	ret=fcntl(fd, F_RESVSP64, &fl);

	if (ret != 0)
		return errno;


	fstat64(fd, &sbuf);
	if (new_len > sbuf.st_size)
		ftruncate64(fd, new_len);
	return 0;
#else
	return ENOSYS;
#endif
}
