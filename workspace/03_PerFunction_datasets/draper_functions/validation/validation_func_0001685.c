git_remote_get(git_remote **out, git_config *cfg, const char *name)
{
	git_remote *remote;
	char *buf = NULL;
	const char *val;
	int ret, error, buf_len;

	remote = git__malloc(sizeof(git_remote));
	if (remote == NULL)
		return GIT_ENOMEM;

	memset(remote, 0x0, sizeof(git_remote));
	remote->name = git__strdup(name);
	if (remote->name == NULL) {
		error = GIT_ENOMEM;
		goto cleanup;
	}


	buf_len = STRLEN("remote.") + STRLEN(".fetch") + strlen(name) + 1;
	buf = git__malloc(buf_len);
	if (buf == NULL) {
		error = GIT_ENOMEM;
		goto cleanup;
	}

	ret = snprintf(buf, buf_len, "%s.%s.%s", "remote", name, "url");
	if (ret < 0) {
		error = git__throw(GIT_EOSERR, "Failed to build config var name");
		goto cleanup;
	}

	error = git_config_get_string(cfg, buf, &val);
	if (error < GIT_SUCCESS) {
		error = git__rethrow(error,  "Remote's url doesn't exist");
		goto cleanup;
	}

	remote->url = git__strdup(val);
	if (remote->url == NULL) {
		error = GIT_ENOMEM;
		goto cleanup;
	}

	ret = snprintf(buf, buf_len, "%s.%s.%s", "remote", name, "fetch");
	if (ret < 0) {
		error = git__throw(GIT_EOSERR, "Failed to build config var name");
		goto cleanup;
	}

	error = parse_remote_refspec(cfg, &remote->fetch, buf);
	if (error < GIT_SUCCESS) {
		error = git__rethrow(error, "Failed to get fetch refspec");
		goto cleanup;
	}

	ret = snprintf(buf, buf_len, "%s.%s.%s", "remote", name, "push");
	if (ret < 0) {
		error = git__throw(GIT_EOSERR, "Failed to build config var name");
		goto cleanup;
	}

	error = parse_remote_refspec(cfg, &remote->push, buf);

	if (error == GIT_ENOTFOUND)
		error = GIT_SUCCESS;

	if (error < GIT_SUCCESS)
		goto cleanup;

	*out = remote;

cleanup:
	free(buf);
	if (error < GIT_SUCCESS)
		git_remote_free(remote);

	return error;
}
