grab_file(const void *ctx, const char *filename, size_t *size)
{
	int fd;
	char *buffer;

	if (!filename)
		fd = dup(STDIN_FILENO);
	else
		fd = open(filename, O_RDONLY, 0);

	if (fd < 0)
		return NULL;

	buffer = grab_fd(ctx, fd, size);
	close_noerr(fd);
	return buffer;
}
