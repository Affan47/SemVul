static char *cfg_make_fullpath(const char *dir, const char *file)
{
	int np;
	char *path;
	size_t len;

	if (!dir || !file) {
		errno = EINVAL;
		return NULL;
	}

	len = strlen(dir) + strlen(file) + 2;
	path = malloc(len);
	if (!path)
		return NULL;

	np = snprintf(path, len, "%s/%s", dir, file);


	assert(np < (int)len);

	return path;
}
