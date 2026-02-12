int git_path_dirname_r(git_buf *buffer, const char *path)
{
	const char *endp;
	int is_prefix = 0, len;


	if (path == NULL || *path == '\0') {
		path = ".";
		len = 1;
		goto Exit;
	}


	endp = path + strlen(path) - 1;
	while (endp > path && *endp == '/')
		endp--;

	if (endp - path + 1 > INT_MAX) {
		git_error_set(GIT_ERROR_INVALID, "path too long");
		len = -1;
		goto Exit;
	}

	if ((len = win32_prefix_length(path, (int)(endp - path + 1))) > 0) {
		is_prefix = 1;
		goto Exit;
	}


	while (endp > path && *endp != '/')
		endp--;


	if (endp == path) {
		path = (*endp == '/') ? "/" : ".";
		len = 1;
		goto Exit;
	}

	do {
		endp--;
	} while (endp > path && *endp == '/');

	if (endp - path + 1 > INT_MAX) {
		git_error_set(GIT_ERROR_INVALID, "path too long");
		len = -1;
		goto Exit;
	}

	if ((len = win32_prefix_length(path, (int)(endp - path + 1))) > 0) {
		is_prefix = 1;
		goto Exit;
	}


	len = (int)(endp - path + 1);

Exit:
	if (buffer) {
		if (git_buf_set(buffer, path, len) < 0)
			return -1;
		if (is_prefix && git_buf_putc(buffer, '/') < 0)
			return -1;
	}

	return len;
}
