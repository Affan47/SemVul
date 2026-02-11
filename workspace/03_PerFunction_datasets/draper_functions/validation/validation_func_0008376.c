file_path_set(file_path_t *fp, const char *dir, const char *name)
{
	g_assert(fp);
	g_assert(dir);
	g_assert(name);


	if (!is_absolute_path(dir)) {
		s_carp("%s(): ignoring non-absolute path \"%s\" for \"%s\"",
			G_STRFUNC, dir, name);

		fp->dir = NULL;
		fp->name = NULL;
	} else {
		fp->dir = dir;
		fp->name = name;
	}
}
