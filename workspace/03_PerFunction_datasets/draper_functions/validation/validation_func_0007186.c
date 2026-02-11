git_config_set_multivar(git_config *cfg, const char *name, const char *regexp, const char *value)
{
	git_config_backend *file;
	file_internal *internal;

	internal = git_vector_get(&cfg->files, 0);
	if (!internal || !internal->file)
		return config_error_nofiles(name);
	file = internal->file;

	return file->set_multivar(file, name, regexp, value);
}
