mmap_read(char *path)
{
	int fd = 0, r;
	char *buf, *ret;
	struct stat st;

	fd = open (path, O_RDONLY);
	if (fd < 0) {
		warn("open: %s", path);
		return NULL;
	}

	if (fstat(fd, &st) == -1) {
		warn("fstat: %s", path);
		return NULL;
	}

	buf = mmap(0, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (buf == MAP_FAILED) {
		err(EX_SOFTWARE, "mmap");
	}

	r = close(fd);
	if (r == -1) {
		err(EX_OSFILE, "close");
	}

	ret = strdup(buf);


	r = munmap(buf, st.st_size);
	if (r == -1) {
		err(EX_SOFTWARE, "munmap");
	}

	return ret;
}
