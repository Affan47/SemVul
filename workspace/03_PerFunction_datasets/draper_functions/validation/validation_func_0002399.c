dev_size_mb( void)
{
	union {
		unsigned long long blksize64;
		unsigned blksize32;
	} u;

	if (0 == ioctl(fd, BLKGETSIZE64, &u.blksize64)) {
		u.blksize64 /= (1024 * 1024);
	} else {
		xioctl(fd, BLKGETSIZE, &u.blksize32);
		u.blksize64 = u.blksize32 / (2 * 1024);
	}
	if (u.blksize64 > UINT_MAX)
		return UINT_MAX;
	return u.blksize64;
}
