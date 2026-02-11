discard_blocks(int fd, uint64_t start, uint64_t len)
{
	__uint64_t range[2] = { start, len };

	if (ioctl(fd, BLKDISCARD, &range) < 0)
		return errno;
	return 0;
}
