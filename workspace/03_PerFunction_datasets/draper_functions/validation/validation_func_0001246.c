diff_delta__merge_like_cgit(
	const git_diff_delta *a, const git_diff_delta *b, git_pool *pool)
{
	git_diff_delta *dup = diff_delta__dup(a, pool);
	if (!dup)
		return NULL;

	if (git_oid_cmp(&dup->new_file.oid, &b->new_file.oid) == 0)
		return dup;

	git_oid_cpy(&dup->new_file.oid, &b->new_file.oid);

	dup->new_file.mode = b->new_file.mode;
	dup->new_file.size = b->new_file.size;
	dup->new_file.flags = b->new_file.flags;


	if (git_oid_cmp(&dup->old_file.oid, &dup->new_file.oid) == 0) {
		if (dup->status == GIT_DELTA_DELETED)
			;
		else if (b->status == GIT_DELTA_UNTRACKED ||
				 b->status == GIT_DELTA_IGNORED)
			dup->status = b->status;
		else
			dup->status = GIT_DELTA_UNMODIFIED;
	}
	else if (dup->status == GIT_DELTA_UNMODIFIED ||
			 b->status == GIT_DELTA_DELETED)
		dup->status = b->status;

	return dup;
}
