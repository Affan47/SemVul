awe_search_file_name(char *fresult, int maxlen, char *fname, char *pathlist, char **ext)
{
	char *tok;
	char *path;

	if (strlen(fname) >= maxlen)
		return 0;

	strcpy(fresult, fname);
	if (file_exists(fresult, ext))
		return 1;


	if (fname[0] != '/' && pathlist && *pathlist) {
		path = safe_strdup(pathlist);
		for (tok = strtok(path, ":"); tok; tok = strtok(NULL, ":")) {
			if (*tok && tok[strlen(tok)-1] != '/')
				snprintf(fresult, maxlen, "%s/%s", tok, fname);
			else
				snprintf(fresult, maxlen, "%s%s", tok, fname);
			if (file_exists(fresult, ext)) {
				safe_free(path);
				return 1;
			}
		}
	}
	return 0;
}
