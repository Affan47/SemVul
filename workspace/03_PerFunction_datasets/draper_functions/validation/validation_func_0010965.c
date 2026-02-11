chunk_from_fd(int fd, chunk_t *out)
{
	struct stat sb;
	char *buf, *tmp;
	ssize_t len, total = 0, bufsize;

	if (fstat(fd, &sb) == 0 && S_ISREG(sb.st_mode))
	{
		bufsize = sb.st_size;
	}
	else
	{
		bufsize = 256;
	}
	buf = malloc(bufsize);
	if (!buf)
	{
		return FALSE;
	}

	while (TRUE)
	{
		len = read(fd, buf + total, bufsize - total);
#ifdef WIN32
		if (len == -1 && errno == EBADF)
		{
			len = recv(fd, buf + total, bufsize - total, 0);
		}
#endif
		if (len < 0)
		{
			free(buf);
			return FALSE;
		}
		if (len == 0)
		{
			break;
		}
		total += len;
		if (total == bufsize)
		{
			bufsize *= 2;
			tmp = realloc(buf, bufsize);
			if (!tmp)
			{
				free(buf);
				return FALSE;
			}
			buf = tmp;
		}
	}
	if (total == 0)
	{
		free(buf);
		buf = NULL;
	}
	else if (total < bufsize)
	{
		buf = realloc(buf, total);
	}
	*out = chunk_create(buf, total);
	return TRUE;
}
