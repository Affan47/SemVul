update_index_cb(
	const git_diff_delta *delta,
	float progress,
	void *payload)
{
	struct cb_data *data = (struct cb_data *)payload;
	const char *add_path = NULL;

	GIT_UNUSED(progress);

	switch (delta->status) {
	case GIT_DELTA_IGNORED:
		if (data->include_ignored)
			add_path = delta->new_file.path;
		break;

	case GIT_DELTA_UNTRACKED:
		if (data->include_untracked)
			add_path = delta->new_file.path;
		break;

	case GIT_DELTA_ADDED:
	case GIT_DELTA_MODIFIED:
		if (data->include_changed)
			add_path = delta->new_file.path;
		break;

	case GIT_DELTA_DELETED:
		if (!data->include_changed)
			break;
		if (git_index_find(NULL, data->index, delta->old_file.path) == 0)
			data->error = git_index_remove(
				data->index, delta->old_file.path, 0);
		break;

	default:

		giterr_set(
			GITERR_INVALID,
			"Cannot update index. Unimplemented status (%d)",
			delta->status);
		data->error = -1;
		break;
	}

	if (add_path != NULL)
		data->error = git_index_add_bypath(data->index, add_path);

	return data->error;
}
