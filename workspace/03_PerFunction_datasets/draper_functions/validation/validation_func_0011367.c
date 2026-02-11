rename_fetch_refspecs(
	git_remote *remote,
	const char *new_name,
	int (*callback)(const char *problematic_refspec, void *payload),
	void *payload)
{
	git_config *config;
	const git_refspec *fetch_refspec;
	git_buf dst_prefix = GIT_BUF_INIT, serialized = GIT_BUF_INIT;
	const char* pos;
	int error = -1;

	fetch_refspec = git_remote_fetchspec(remote);


	if (fetch_refspec->src == NULL &&
		fetch_refspec->dst == NULL)
		return 0;

	if (git_refspec__serialize(&serialized, fetch_refspec) < 0)
		goto cleanup;


	if (remote->name == '\0') {
		error = (callback(git_buf_cstr(&serialized), payload) < 0) ? GIT_EUSER : 0;
		goto cleanup;
	}

	if (git_buf_printf(&dst_prefix, ":refs/remotes/%s/", remote->name) < 0)
		goto cleanup;

	pos = strstr(git_buf_cstr(&serialized), git_buf_cstr(&dst_prefix));


	if (!pos) {
		error = (callback(git_buf_cstr(&serialized), payload) < 0) ? GIT_EUSER : 0;
		goto cleanup;
	}

	if (git_buf_splice(
		&serialized,
		pos - git_buf_cstr(&serialized) + strlen(":refs/remotes/"),
		strlen(remote->name), new_name,
		strlen(new_name)) < 0)
			goto cleanup;

	git_refspec__free(&remote->fetch);

	if (git_refspec__parse(&remote->fetch, git_buf_cstr(&serialized), true) < 0)
		goto cleanup;

	if (git_repository_config__weakptr(&config, remote->repo) < 0)
		goto cleanup;

	error = update_config_refspec(config, new_name, &remote->fetch, GIT_DIR_FETCH);

cleanup:
	git_buf_free(&serialized);
	git_buf_free(&dst_prefix);
	return error;
}
