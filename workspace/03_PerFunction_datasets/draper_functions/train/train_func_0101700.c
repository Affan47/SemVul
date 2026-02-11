multiplexor(Boolean_t block)
{
	struct timeval tv, *tvp = NULL;
	int j;
	fd_t maxfd = 0;
	ssize_t bytes;
	struct stream *stream, *prev, *next;
	fd_set fds[3];
	char *rdbuff = NULL;

	for (j = 0; j < 3; j++)
		FD_ZERO(&fds[j]);
	FD_SET(0, &fds[0]);
	FD_SET(0, &fds[2]);
	for (stream = streams; stream; stream = stream->next) {
		FD_SET(stream->fd, &fds[!!stream->data]);
		FD_SET(stream->fd, &fds[2]);
		if (stream->fd > maxfd)
			maxfd = stream->fd;
	}
	if (block)
		tvp = NULL;
	else
		memset(tvp = &tv, 0, sizeof tv);

	errno = 0;
	if (select(maxfd + 1, &fds[0], &fds[1], &fds[2], tvp) < 0)
		return errno != EAGAIN && errno != EINTR;

	for (prev = NULL, stream = streams; stream; stream = next) {
		next = stream->next;
		if (!FD_ISSET(stream->fd, &fds[!!stream->data]) &&
		    !FD_ISSET(stream->fd, &fds[2])) {
			prev = stream;
			continue;
		}
		if (stream->data)
			bytes = 0;
		else {
			if (!rdbuff)
				rdbuff = allocate(1024);
			errno = 0;
			bytes = read(stream->fd, rdbuff, 1023);
		}
		if (stream->activity(stream, rdbuff, bytes))
			prev = stream;
		else
			stream_destroy(stream, prev);
	}

	RELEASE(rdbuff);
	return FD_ISSET(0, &fds[0]) || FD_ISSET(0, &fds[2]);
}
