_write_bytes(int fd, char *buf, const size_t size)
{
	size_t bytes_remaining, bytes_written;
	char *ptr;

	bytes_remaining = size;
	ptr = buf;
	while (bytes_remaining > 0) {
		bytes_written = write(fd, ptr, bytes_remaining);
		if (bytes_written <= 0)
			return (size - bytes_remaining);
		bytes_remaining -= bytes_written;
		ptr += bytes_written;
	}
	return size;
}
