try_file_to_buffer(char *buffer, size_t bufsiz, const char *format, ...)
{
	char path[4096];
	int fd;
	size_t len = 0;
	ssize_t nread = 0;
	va_list pa;

	if (G_UNLIKELY(bufsiz <= sizeof(char*)))
	  g_warning("Huhu, bufsiz of %lu looks bad", (gulong)bufsiz);

	va_start(pa, format);


	g_vsnprintf(path, sizeof path, format, pa);

	va_end(pa);

	bufsiz--;
	buffer [0] = '\0';

	if((fd = open (path, O_RDONLY)) < 0)
		return TRY_FILE_TO_BUFFER_OPEN;

	while (len < bufsiz) {
		nread = read (fd, buffer + len, bufsiz - len);

		if (G_UNLIKELY(nread < 0)) {
			if (errno == EINTR)
				continue;
			else
				break;
		}

		len += nread;

		if (nread == 0)
			break;
	}

	close (fd);

	if (nread < 0)
		return TRY_FILE_TO_BUFFER_READ;

	buffer [len] = '\0';

	return TRY_FILE_TO_BUFFER_OK;
}
