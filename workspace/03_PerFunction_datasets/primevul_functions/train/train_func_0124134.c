static const char *cleanup_path(const char *path)
{

	if (skip_prefix(path, "./", &path)) {
		while (*path == '/')
			path++;
	}
	return path;
}
