write_str_safe(int fd, const char *buf, size_t buflen)
{
	size_t todo = buflen;
	size_t done = 0;

	do {
		ssize_t r = write(fd, buf + done, todo);

		if (r == 0)
			break;
		else if (r > 0) {
			todo -= r;
			done += r;
		} else {
			if (errno == EAGAIN || errno == EWOULDBLOCK ||
								errno == EINTR)
				continue;
			else
				return -errno;
		}
	} while (todo > 0);

	return done;
}
