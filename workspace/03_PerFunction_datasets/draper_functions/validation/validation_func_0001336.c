git_diff_driver_content_is_binary(
	git_diff_driver *driver, const char *content, size_t content_len)
{
	const git_buf search = { (char *)content, 0, min(content_len, 4000) };

	GIT_UNUSED(driver);


	if (git_buf_text_contains_nul(&search))
		return 1;

	return 0;
}
