are_symlinks_supported(const char *wd_path)
{
	git_buf path = GIT_BUF_INIT;
	int fd;
	struct stat st;
	int symlinks_supported = -1;

	if ((fd = git_futils_mktmp(&path, wd_path, 0666)) < 0 ||
		p_close(fd) < 0 ||
		p_unlink(path.ptr) < 0 ||
		p_symlink("testing", path.ptr) < 0 ||
		p_lstat(path.ptr, &st) < 0)
		symlinks_supported = false;
	else
		symlinks_supported = (S_ISLNK(st.st_mode) != 0);

	(void)p_unlink(path.ptr);
	git_buf_free(&path);

	return symlinks_supported;
}
