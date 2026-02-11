writen(int fd, const void *buf, size_t len)
{
	int o = 0, n;
	char *ptr = (char*)buf;

	while (len > 0) {
		if ((n = write(fd, ptr+o, len)) <= 0) {
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				return o;
			return n;
		}
		len -= n;
		o += n;
	}
	return o;
}
