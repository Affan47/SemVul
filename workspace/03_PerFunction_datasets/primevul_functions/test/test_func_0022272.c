const char *cgit_repobasename(const char *reponame)
{

	static char rvbuf[1024];
	int p;
	const char *rv;
	strncpy(rvbuf, reponame, sizeof(rvbuf));
	if (rvbuf[sizeof(rvbuf)-1])
		die("cgit_repobasename: truncated repository name '%s'", reponame);
	p = strlen(rvbuf)-1;

	while (p && rvbuf[p] == '/') rvbuf[p--] = 0;

	if (p >= 3 && starts_with(&rvbuf[p-3], ".git")) {
		p -= 3; rvbuf[p--] = 0;
	}

	while ( p && rvbuf[p] == '/') rvbuf[p--] = 0;

	rv = strrchr(rvbuf,'/');
	if (rv)
		return ++rv;
	return rvbuf;
}
