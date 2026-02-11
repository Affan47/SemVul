test_network_remote_rename__renamed_name_is_persisted(void)
{
	git_remote *renamed;
	git_repository *another_repo;
	git_strarray problems = {0};

	cl_git_fail(git_remote_load(&renamed, _repo, "just/renamed"));

	cl_git_pass(git_remote_rename(&problems, _repo, _remote_name, "just/renamed"));
	cl_assert_equal_i(0, problems.count);
	git_strarray_free(&problems);

	cl_git_pass(git_repository_open(&another_repo, "testrepo.git"));
	cl_git_pass(git_remote_load(&renamed, _repo, "just/renamed"));

	git_remote_free(renamed);
	git_repository_free(another_repo);
}
