int check_filename(const char *prefix, const char *arg)
{
	const char *name;
	struct stat st;

	name = prefix ? prefix_filename(prefix, strlen(prefix), arg) : arg;
	if (!lstat(name, &st))
		return 1;
	if (errno == ENOENT || errno == ENOTDIR)
		return 0;
	die_errno("failed to stat '%s'", arg);
}
