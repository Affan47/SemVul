encap_mkdirhier(char *path, encap_mkdirhier_printfunc_t *printfunc,
		  void *state)
{
	char src[MAXPATHLEN], dst[MAXPATHLEN] = "";
	char *dirp, *nextp = src;
	int retval = 1;

	if (strlcpy(src, path, sizeof(src)) > sizeof(src))
	{
		errno = ENAMETOOLONG;
		return -1;
	}

	while ((dirp = strsep(&nextp, "/")) != NULL)
	{
		if (*dirp == '\0')
			continue;

		if (dst[0] != '\0' || path[0] == '/')
			strcat(dst, "/");
		strcat(dst, dirp);

		if (mkdir(dst, 0777) == -1)
		{
			if (errno != EEXIST)
				return -1;
		}
		else
		{
			if (printfunc != NULL)
				(*printfunc)(state, dst);
			retval = 0;
		}
	}

	return retval;
}
