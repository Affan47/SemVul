int git_path_basename_r(git_buf *buffer, const char *path)
{
	const char *endp, *startp;
	int len, result;


	if (path == NULL || *path == '\0') {
		startp = ".";
		len		= 1;
		goto Exit;
	}


	endp = path + strlen(path) - 1;
	while (endp > path && *endp == '/')
		endp--;


	if (endp == path && *endp == '/') {
		startp = "/";
		len	= 1;
		goto Exit;
	}


	startp = endp;
	while (startp > path && *(startp - 1) != '/')
		startp--;


	len = (int)(endp - startp + 1);

Exit:
	result = len;

	if (buffer != NULL && git_buf_set(buffer, startp, len) < 0)
		return -1;

	return result;
}
