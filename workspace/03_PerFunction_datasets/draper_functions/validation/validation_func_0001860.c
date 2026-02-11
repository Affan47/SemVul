VerifyFileRange(char *path, char *last_file) {
char *p, *q, *r;

	r = strdup(path);
	p = strrchr(r, '/');
	while ( p ) {
		*p = '\0';

		q = GuessSubDir(r, last_file);
		if ( q ) {
			free(r);
			return q;
		}
		p = strrchr(r, '/');
	}

	free(r);
	return last_file;

}
