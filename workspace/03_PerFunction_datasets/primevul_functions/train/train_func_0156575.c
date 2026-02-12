int lrename (const char *old, const char *new)
{
	int res;
	char *r = NULL;

#if defined(S_ISLNK)
#ifndef __GLIBC__
	char resolved_path[PATH_MAX];
#endif
	struct stat sb;
	if (lstat (new, &sb) == 0 && S_ISLNK (sb.st_mode)) {
#ifdef __GLIBC__
		r = realpath (new, NULL);
#else
		r = realpath (new, resolved_path);
#endif
		if (NULL == r) {
			perror ("realpath in lrename()");
		} else {
			new = r;
		}
	}
#endif

	res = rename (old, new);

#ifdef __GLIBC__
	if (NULL != r) {
		free (r);
	}
#endif

	return res;
}
