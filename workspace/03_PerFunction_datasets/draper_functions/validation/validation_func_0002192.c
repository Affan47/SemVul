test_checkout_tree__can_remove_untracked(void)
{
	git_checkout_opts opts = GIT_CHECKOUT_OPTS_INIT;

	opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_REMOVE_UNTRACKED;

	cl_git_mkfile("testrepo/untracked_file", "as you wish");
	cl_assert(git_path_isfile("testrepo/untracked_file"));

	cl_git_pass(git_checkout_head(g_repo, &opts));

	cl_assert(!git_path_isfile("testrepo/untracked_file"));
}
