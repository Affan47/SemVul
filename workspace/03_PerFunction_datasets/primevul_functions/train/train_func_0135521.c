static int path_matches(const char *pathname, int pathlen,
			const char *pattern,
			const char *base, int baselen)
{
	if (!strchr(pattern, '/')) {

		const char *basename = strrchr(pathname, '/');
		basename = basename ? basename + 1 : pathname;
		return (fnmatch(pattern, basename, 0) == 0);
	}


	if (*pattern == '/')
		pattern++;
	if (pathlen < baselen ||
	    (baselen && pathname[baselen] != '/') ||
	    strncmp(pathname, base, baselen))
		return 0;
	if (baselen != 0)
		baselen++;
	return fnmatch(pattern, pathname + baselen, FNM_PATHNAME) == 0;
}
