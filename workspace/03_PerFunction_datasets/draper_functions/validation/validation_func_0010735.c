alloc_and_open(const char *path, const char *file)
{
	struct lnstat_file *lf;


	lf = malloc(sizeof(*lf));
	if (!lf)
		return NULL;


	memset(lf, 0, sizeof(*lf));


	strcpy(lf->basename, file);
	strcpy(lf->path, path);
	strcat(lf->path, "/");
	strcat(lf->path, lf->basename);


	lf->interval.tv_sec = 1;


	lf->fp = fopen(lf->path, "r");
	if (!lf->fp) {
		free(lf);
		return NULL;
	}

	return lf;
}
