git_config_add_file_ondisk(git_config *cfg, const char *path, int priority)
{
	git_config_file *file = NULL;

	if (git_config_file__ondisk(&file, path) < 0)
		return -1;

	if (git_config_add_file(cfg, file, priority) < 0) {


		file->free(file);
		return -1;
	}

	return 0;
}
