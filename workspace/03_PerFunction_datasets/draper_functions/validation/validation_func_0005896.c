shared_special(const char *path)
{
	shared_file_t *sf;
	filestat_t file_stat;

	sf = htable_lookup(special_names, path);

	if (sf == NULL)
		return NULL;

	if (-1 == stat(sf->file_path, &file_stat)) {
		g_warning("can't stat %s: %m", sf->file_path);
		return NULL;
	}

	if (!S_ISREG(file_stat.st_mode)) {
		g_warning("file %s is no longer a plain file", sf->file_path);
		return NULL;
	}


	sf->file_size = file_stat.st_size;
	sf->mtime = file_stat.st_mtime;
	sf->ctime = file_stat.st_ctime;

	return sf;
}
