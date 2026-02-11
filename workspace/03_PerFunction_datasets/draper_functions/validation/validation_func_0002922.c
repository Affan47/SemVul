stream_create_unix(char *uri)
{
	struct sockaddr_un addr;
	int len, fd;

	len = stream_parse_uri_unix(uri, &addr);
	if (len == -1)
	{
		DBG1(DBG_NET, "invalid stream URI: '%s'", uri);
		return NULL;
	}
	fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (fd < 0)
	{
		DBG1(DBG_NET, "opening socket '%s' failed: %s", uri, strerror(errno));
		return NULL;
	}
	if (connect(fd, (struct sockaddr*)&addr, len) < 0)
	{
		DBG1(DBG_NET, "connecting to '%s' failed: %s", uri, strerror(errno));
		close(fd);
		return NULL;
	}
	return stream_create_from_fd(fd);
}
