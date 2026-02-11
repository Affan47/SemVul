fsdb_search_dir (const TCHAR *dirname, TCHAR *rel)
{
	TCHAR *p = 0;
	int de;
	my_opendir_s *dir;
	TCHAR fn[MAX_DPATH];

	dir = my_opendir (dirname);

	if (! dir)
		return 0;

	while (p == 0 && (de = my_readdir (dir, fn)) != 0) {
		if (strcmp (fn, rel) == 0)
			p = rel;
		else if (strcasecmp (fn, rel) == 0)
			p = my_strdup (fn);
	}
	my_closedir (dir);
	return p;
}
