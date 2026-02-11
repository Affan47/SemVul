read_chunk_from_file(const char *path, unsigned nr,
		unsigned char *chunk)
{
	int len, n, fd;
	off_t offset;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return -EIO;

	offset = (off_t)nr * CHUNK_SIZE;
	if (lseek(fd, offset, SEEK_SET) == (off_t)-1) {
		close(fd);
		return -EIO;
	}

	for (len = 0; len < CHUNK_SIZE; ) {
		n = read(fd, chunk + len, CHUNK_SIZE - len);
		if (n < 0) {
			if (errno == EINTR)
				continue;
			close(fd);
			return -EIO;
		}
		if (!n)
			break;
		len += n;
	}

	close(fd);
	return len;
}
