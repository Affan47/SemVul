bool git_path_does_fs_decompose_unicode(const char *root)
{
	git_buf path = GIT_BUF_INIT;
	int fd;
	bool found_decomposed = false;
	char tmp[6];


	if (git_buf_joinpath(&path, root, nfc_file) < 0 ||
		(fd = p_mkstemp(path.ptr)) < 0)
		goto done;
	p_close(fd);


	memcpy(tmp, path.ptr + path.size - sizeof(tmp), sizeof(tmp));


	if (git_buf_joinpath(&path, root, nfd_file) < 0)
		goto done;
	memcpy(path.ptr + path.size - sizeof(tmp), tmp, sizeof(tmp));

	found_decomposed = git_path_exists(path.ptr);


	if (git_buf_joinpath(&path, root, nfc_file) < 0)
		goto done;
	memcpy(path.ptr + path.size - sizeof(tmp), tmp, sizeof(tmp));

	(void)p_unlink(path.ptr);

done:
	git_buf_dispose(&path);
	return found_decomposed;
}
