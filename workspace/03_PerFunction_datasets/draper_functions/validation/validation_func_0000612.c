vd_get_http_results (int sock, size_t *bytes_read,
		     VDCallback vd_callback,
		     VDError *ex)
{
	const unsigned max_buf    = 50000;
	const unsigned chunk_size = 512;

	char *buf;
	int result;


	buf = (char*) malloc (max_buf);
	if (!buf) {
		*ex   = VD_ERR_MEM;
		return NULL;
	}

	*bytes_read = 0;
	while (*bytes_read < max_buf) {

		result = read (sock, buf + *bytes_read, chunk_size);
		if (result == -1 || result == 0)
			break;

		*bytes_read += result;
	}

	if (result == -1) {
		free (buf);
		*ex   = VD_ERR_READ;
		return NULL;
	}

	return buf;
}
