merge_branches(git_repository *repo,
	const char *ours_branch, const char *theirs_branch,
	git_merge_options *merge_opts, git_checkout_options *checkout_opts)
{
	git_reference *head_ref, *theirs_ref;
	git_annotated_commit *theirs_head;
	git_checkout_options head_checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;

	head_checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	cl_git_pass(git_reference_symbolic_create(&head_ref, repo, "HEAD", ours_branch, 1, NULL, NULL));
	cl_git_pass(git_checkout_head(repo, &head_checkout_opts));

	cl_git_pass(git_reference_lookup(&theirs_ref, repo, theirs_branch));
	cl_git_pass(git_annotated_commit_from_ref(&theirs_head, repo, theirs_ref));

	cl_git_pass(git_merge(repo, (const git_annotated_commit **)&theirs_head, 1, merge_opts, checkout_opts));

	git_reference_free(head_ref);
	git_reference_free(theirs_ref);
	git_annotated_commit_free(theirs_head);

	return 0;
}
