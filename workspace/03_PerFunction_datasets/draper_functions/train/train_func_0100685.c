git_commit_create(
		git_oid *oid,
		git_repository *repo,
		const char *update_ref,
		const git_signature *author,
		const git_signature *committer,
		const char *message,
		const git_tree *tree,
		int parent_count,
		const git_commit *parents[])
{
	size_t final_size = 0;
	int message_length, author_length, committer_length;

	char *author_str, *committer_str;

	int error, i;
	git_odb_stream *stream;

	message_length = strlen(message);
	author_length = git_signature__write(&author_str, "author", author);
	committer_length = git_signature__write(&committer_str, "committer", committer);

	if (author_length < 0 || committer_length < 0)
		return git__throw(GIT_EINVALIDARGS, "Cannot create commit. Failed to parse signature");

	final_size += GIT_OID_LINE_LENGTH("tree");
	final_size += GIT_OID_LINE_LENGTH("parent") * parent_count;
	final_size += author_length;
	final_size += committer_length;
	final_size += 1 + message_length;

	if ((error = git_odb_open_wstream(&stream, repo->db, final_size, GIT_OBJ_COMMIT)) < GIT_SUCCESS)
		return git__rethrow(error, "Failed to create commit");

	if (git_object_owner((const git_object *)tree) != repo)
		return git__throw(GIT_EINVALIDARGS, "The given tree does not belong to this repository");

	git__write_oid(stream, "tree", git_object_id((const git_object *)tree));

	for (i = 0; i < parent_count; ++i) {
		if (git_object_owner((const git_object *)parents[i]) != repo)
			return git__throw(GIT_EINVALIDARGS, "The given parent does not belong to this repository");

		git__write_oid(stream, "parent", git_object_id((const git_object *)parents[i]));
	}

	stream->write(stream, author_str, author_length);
	free(author_str);

	stream->write(stream, committer_str, committer_length);
	free(committer_str);

	stream->write(stream, "\n", 1);
	stream->write(stream, message, message_length);

	error = stream->finalize_write(oid, stream);
	stream->free(stream);

	if (error == GIT_SUCCESS && update_ref != NULL) {
		git_reference *head;

		error = git_reference_lookup(&head, repo, update_ref);
		if (error < GIT_SUCCESS)
			return git__rethrow(error, "Failed to create commit");

		error = git_reference_resolve(&head, head);
		if (error < GIT_SUCCESS) {
			if (error != GIT_ENOTFOUND)
				return git__rethrow(error, "Failed to create commit");


			return git_reference_create_oid(&head, repo, git_reference_target(head), oid, 1);
		}

		error = git_reference_set_oid(head, oid);
	}

	if (error < GIT_SUCCESS)
		return git__rethrow(error, "Failed to create commit");

	return GIT_SUCCESS;
}
