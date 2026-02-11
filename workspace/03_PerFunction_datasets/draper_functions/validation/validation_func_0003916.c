splitpath(pathp, resolved, needlfn)
CONST char **pathp;
char *resolved;
int needlfn;
{
	char dir[DOSMAXPATHLEN];
	int i, j;

	Xstrcpy(dir, *pathp);
	for (i = 1, j = 2; dir[j]; j++) {
		if (iswsjis(dir, j)) j++;
		else if (dir[j] == '/' || dir[j] == '\\') i = j;
	}

	*pathp += i + 1;
	if (i < 3) dir[i++] = _SC_;
	dir[i] = '\0';

	if (i <= 3 && isdotdir(*pathp)) {
		doserrno = ENOENT;
		return(NULL);
	}

	return(_dosopendir(dir, resolved, needlfn));
}
