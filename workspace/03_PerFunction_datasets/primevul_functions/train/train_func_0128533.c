static int checkout_create_conflicts(checkout_data *data)
{
	checkout_conflictdata *conflict;
	size_t i;
	int error = 0;

	git_vector_foreach(&data->update_conflicts, i, conflict) {


		if (conflict->ours == NULL && conflict->theirs == NULL)
			error = 0;

		else if ((data->strategy & GIT_CHECKOUT_USE_OURS) &&
			conflict->ours)
			error = checkout_write_entry(data, conflict, conflict->ours);
		else if ((data->strategy & GIT_CHECKOUT_USE_THEIRS) &&
			conflict->theirs)
			error = checkout_write_entry(data, conflict, conflict->theirs);


		else if ((data->strategy & GIT_CHECKOUT_USE_OURS) &&
			!conflict->ours && conflict->name_collision)
			error = 0;
		else if ((data->strategy & GIT_CHECKOUT_USE_THEIRS) &&
			!conflict->theirs && conflict->name_collision)
			error = 0;


		else if (conflict->ours != NULL && conflict->theirs == NULL)
			error = checkout_write_entry(data, conflict, conflict->ours);
		else if (conflict->ours == NULL && conflict->theirs != NULL)
			error = checkout_write_entry(data, conflict, conflict->theirs);


		else if (conflict->one_to_two)
			error = checkout_write_entries(data, conflict);


		else if (S_ISLNK(conflict->ours->mode) &&
			S_ISLNK(conflict->theirs->mode))
			error = checkout_write_entry(data, conflict, conflict->ours);

		else if (S_ISLNK(conflict->ours->mode))
			error = checkout_write_entry(data, conflict, conflict->theirs);
		else if (S_ISLNK(conflict->theirs->mode))
			error = checkout_write_entry(data, conflict, conflict->ours);


		else if (conflict->submodule)
			error = 0;


		else if (conflict->binary)
			error = checkout_write_entry(data, conflict, conflict->ours);

		else if (!error)
			error = checkout_write_merge(data, conflict);


		if (!error && (data->strategy & GIT_CHECKOUT_DONT_UPDATE_INDEX) == 0)
			error = checkout_conflict_update_index(data, conflict);

		if (error)
			break;

		data->completed_steps++;
		report_progress(data,
			conflict->ours ? conflict->ours->path :
			(conflict->theirs ? conflict->theirs->path : conflict->ancestor->path));
	}

	return error;
}
