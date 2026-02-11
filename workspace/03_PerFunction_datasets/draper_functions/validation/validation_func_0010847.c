print_patch_hunk(
	void *data,
	git_diff_delta *d,
	git_diff_range *r,
	const char *header,
	size_t header_len)
{
	diff_print_info *pi = data;

	git_buf_clear(pi->buf);
	if (git_buf_printf(pi->buf, "%.*s", (int)header_len, header) < 0)
		return -1;

	return pi->print_cb(pi->cb_data, d, r, GIT_DIFF_LINE_HUNK_HDR, git_buf_cstr(pi->buf), git_buf_len(pi->buf));
}
