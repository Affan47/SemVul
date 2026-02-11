diff_delta__from_two(
	git_diff *diff,
	git_delta_t status,
	const git_index_entry *old_entry,
	uint32_t old_mode,
	const git_index_entry *new_entry,
	uint32_t new_mode,
	git_oid *new_oid,
	const char *matched_pathspec)
{
	git_diff_delta *delta;
	const char *canonical_path = old_entry->path;

	if (status == GIT_DELTA_UNMODIFIED &&
		DIFF_FLAG_ISNT_SET(diff, GIT_DIFF_INCLUDE_UNMODIFIED))
		return 0;

	if (DIFF_FLAG_IS_SET(diff, GIT_DIFF_REVERSE)) {
		uint32_t temp_mode = old_mode;
		const git_index_entry *temp_entry = old_entry;
		old_entry = new_entry;
		new_entry = temp_entry;
		old_mode = new_mode;
		new_mode = temp_mode;
	}

	delta = diff_delta__alloc(diff, status, canonical_path);
	GITERR_CHECK_ALLOC(delta);
	delta->nfiles = 2;

	git_oid_cpy(&delta->old_file.id, &old_entry->id);
	delta->old_file.size = old_entry->file_size;
	delta->old_file.mode = old_mode;
	delta->old_file.flags |= GIT_DIFF_FLAG_VALID_ID;

	git_oid_cpy(&delta->new_file.id, &new_entry->id);
	delta->new_file.size = new_entry->file_size;
	delta->new_file.mode = new_mode;

	if (new_oid) {
		if (DIFF_FLAG_IS_SET(diff, GIT_DIFF_REVERSE))
			git_oid_cpy(&delta->old_file.id, new_oid);
		else
			git_oid_cpy(&delta->new_file.id, new_oid);
	}

	if (new_oid || !git_oid_iszero(&new_entry->id))
		delta->new_file.flags |= GIT_DIFF_FLAG_VALID_ID;

	return diff_insert_delta(diff, delta, matched_pathspec);
}
