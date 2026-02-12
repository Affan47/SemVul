static int copy_string(struct archive_read* a, int len, int dist) {
	struct rar5* rar = get_context(a);
	const uint64_t cmask = rar->cstate.window_mask;
	const uint64_t write_ptr = rar->cstate.write_ptr +
	    rar->cstate.solid_offset;
	int i;

	if (rar->cstate.window_buf == NULL)
		return ARCHIVE_FATAL;


	for(i = 0; i < len; i++) {
		const ssize_t write_idx = (write_ptr + i) & cmask;
		const ssize_t read_idx = (write_ptr + i - dist) & cmask;
		rar->cstate.window_buf[write_idx] =
		    rar->cstate.window_buf[read_idx];
	}

	rar->cstate.write_ptr += len;
	return ARCHIVE_OK;
}
