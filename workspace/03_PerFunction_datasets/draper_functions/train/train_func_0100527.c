filter_wants(git_remote *remote)
{
	git_remote_head **heads;
	git_refspec tagspec, head;
	int error = 0;
	git_odb *odb;
	size_t i, heads_len;

	git_vector_clear(&remote->refs);
	if ((error = git_refspec__parse(&tagspec, GIT_REFSPEC_TAGS, true)) < 0)
		return error;


	if (remote->active_refspecs.length == 0) {
		if ((error = git_refspec__parse(&head, "HEAD", true)) < 0)
			goto cleanup;

		error = git_refspec__dwim_one(&remote->active_refspecs, &head, &remote->refs);
		git_refspec__free(&head);

		if (error < 0)
			goto cleanup;
	}

	if (git_repository_odb__weakptr(&odb, remote->repo) < 0)
		goto cleanup;

	if (git_remote_ls((const git_remote_head ***)&heads, &heads_len, remote) < 0)
		goto cleanup;

	for (i = 0; i < heads_len; i++) {
		if ((error = maybe_want(remote, heads[i], odb, &tagspec)) < 0)
			break;
	}

cleanup:
	git_refspec__free(&tagspec);

	return error;
}
