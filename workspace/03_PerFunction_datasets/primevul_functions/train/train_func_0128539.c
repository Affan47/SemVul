static int checkout_submodule(
	checkout_data *data,
	const git_diff_file *file)
{
	bool remove_existing = should_remove_existing(data);
	int error = 0;


	if ((data->strategy & GIT_CHECKOUT_UPDATE_ONLY) != 0)
		return 0;

	if ((error = checkout_mkdir(
			data,
			file->path, data->opts.target_directory, data->opts.dir_mode,
			remove_existing ? MKDIR_REMOVE_EXISTING : MKDIR_NORMAL)) < 0)
		return error;

	if ((error = git_submodule_lookup(NULL, data->repo, file->path)) < 0) {


		if (error == GIT_ENOTFOUND) {
			git_error_clear();
			return checkout_submodule_update_index(data, file);
		}

		return error;
	}


	return checkout_submodule_update_index(data, file);
}
