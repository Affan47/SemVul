download_tags_value(git_remote *remote, git_config *cfg)
{
	const char *val;
	git_buf buf = GIT_BUF_INIT;
	int error;


	if (git_buf_printf(&buf, "remote.%s.tagopt", remote->name) < 0)
		return -1;

	error = git_config_get_string(&val, cfg, git_buf_cstr(&buf));
	git_buf_free(&buf);
	if (!error && !strcmp(val, "--no-tags"))
		remote->download_tags = GIT_REMOTE_DOWNLOAD_TAGS_NONE;
	else if (!error && !strcmp(val, "--tags"))
		remote->download_tags = GIT_REMOTE_DOWNLOAD_TAGS_ALL;

	if (error == GIT_ENOTFOUND) {
		giterr_clear();
		error = 0;
	}

	return error;
}
