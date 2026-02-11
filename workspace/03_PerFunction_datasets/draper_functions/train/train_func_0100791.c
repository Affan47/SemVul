v4lconvert_helper_read(struct v4lconvert_data *data, void *b,
		size_t count)
{
	unsigned char *buf = b;
	size_t ret, r = 0;

	while (r < count) {
		ret = read(data->decompress_in_pipe[READ_END], buf + r, count - r);
		if (ret == -1) {
			if (errno == EINTR)
				continue;

			V4LCONVERT_ERR("reading from helper: %s\n", strerror(errno));
			return -1;
		}
		if (ret == 0) {
			V4LCONVERT_ERR("reading from helper: unexpected EOF\n");
			return -1;
		}
		r += ret;
	}

	return 0;
}
