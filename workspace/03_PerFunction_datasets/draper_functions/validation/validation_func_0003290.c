test_network_remote_rename__renaming_a_remote_moves_the_underlying_reference(void)
{
	git_reference *underlying;

	cl_assert_equal_i(GIT_ENOTFOUND, git_reference_lookup(&underlying, _repo, "refs/remotes/just/renamed"));
	cl_git_pass(git_reference_lookup(&underlying, _repo, "refs/remotes/test/master"));
	git_reference_free(underlying);

	cl_git_pass(git_remote_rename(_remote, "just/renamed", dont_call_me_cb, NULL));

	cl_assert_equal_i(GIT_ENOTFOUND, git_reference_lookup(&underlying, _repo, "refs/remotes/test/master"));
	cl_git_pass(git_reference_lookup(&underlying, _repo, "refs/remotes/just/renamed/master"));
	git_reference_free(underlying);
}
