globextend(const gchar *path, wapi_glob_t *pglob, size_t *limitp)
{
	char **pathv;
	int i;
	u_int newsize, len;
	char *copy;
	const gchar *p;

	newsize = sizeof(*pathv) * (2 + pglob->gl_pathc + pglob->gl_offs);
	pathv = pglob->gl_pathv ? realloc((char *)pglob->gl_pathv, newsize) :
	    malloc(newsize);
	if (pathv == NULL) {
		if (pglob->gl_pathv) {
			free(pglob->gl_pathv);
			pglob->gl_pathv = NULL;
		}
		return(WAPI_GLOB_NOSPACE);
	}

	if (pglob->gl_pathv == NULL && pglob->gl_offs > 0) {

		pathv += pglob->gl_offs;
		for (i = pglob->gl_offs; --i >= 0; )
			*--pathv = NULL;
	}
	pglob->gl_pathv = pathv;

	for (p = path; *p++;)
		;
	len = (size_t)(p - path);
	*limitp += len;
	if ((copy = malloc(len)) != NULL) {
		if (g_Ctoc(path, copy, len)) {
			free(copy);
			return(WAPI_GLOB_NOSPACE);
		}
		pathv[pglob->gl_offs + pglob->gl_pathc++] = copy;
	}
	pathv[pglob->gl_offs + pglob->gl_pathc] = NULL;

#if 0

	if ((pglob->gl_flags & WAPI_GLOB_LIMIT) &&
	    newsize + *limitp >= ARG_MAX) {
		errno = 0;
		return(WAPI_GLOB_NOSPACE);
	}
#endif

	return(copy == NULL ? WAPI_GLOB_NOSPACE : 0);
}
