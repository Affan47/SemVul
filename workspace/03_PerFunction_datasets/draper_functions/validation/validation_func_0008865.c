read_line_buffer(Line_Buffer *line_buffer, char *line, size_t max_line_length)
{
    char *line_p;
    char *newline;
    size_t search_length;
    size_t additional_length;
    size_t line_length;
    fd_set fdset;
    struct timeval timeval;
    int select_result;
    ssize_t read_result;


    if (line_buffer->file < 0)
	return -1;
    if (max_line_length == 0)
	return -1;


    line_length = 0;
    line_p = line;

    for (;;) {
	if (0 < line_buffer->cache_length) {


	    if (max_line_length - line_length < line_buffer->cache_length)
		search_length = max_line_length - line_length;
	    else
		search_length = line_buffer->cache_length;

	    newline = (char *)memchr(line_buffer->buffer, '\n', search_length);


	    if (newline != NULL)
		additional_length = newline - line_buffer->buffer + 1;
	    else
		additional_length = search_length;
	    memcpy(line_p, line_buffer->buffer, additional_length);
	    line_p += additional_length;
	    line_length += additional_length;
	    line_buffer->cache_length -= additional_length;


	    memmove(line_buffer->buffer,
		line_buffer->buffer + additional_length,
		line_buffer->cache_length);

	    if (newline != NULL)
		break;
	}


	if (max_line_length <= line_length)
	    return line_length;


	errno = 0;
	FD_ZERO(&fdset);
	FD_SET(line_buffer->file, &fdset);

	if (line_buffer->timeout == 0) {
	    select_result = select(line_buffer->file + 1, &fdset, NULL, NULL,
		NULL);
	} else {
	    timeval.tv_sec = line_buffer->timeout;
	    timeval.tv_usec = 0;
	    select_result = select(line_buffer->file + 1, &fdset, NULL, NULL,
		&timeval);
	}
	if (select_result < 0) {
	    if (errno == EINTR)
		continue;
	    return -1;
	} else if (select_result == 0) {
	    return -1;
	}


	errno = 0;
	read_result = recv(line_buffer->file, line_buffer->buffer,
	    LINEBUF_BUFFER_SIZE, 0);
	if (read_result < 0) {
	    if (errno == EINTR)
		continue;
	    return -1;
	} else if (read_result == 0) {
	    if (line_length == 0) {
		return -1;
	    }
	    return line_length;
	}
	line_buffer->cache_length += read_result;
    }


    line_p--;
    *line_p = '\0';
    line_length--;


    if (0 < line_length && *(line_p - 1) == '\r') {
	line_p--;
	*line_p = '\0';
	line_length--;
    }

    return line_length;
}
