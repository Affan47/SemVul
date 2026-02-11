test_blame_simple__can_restrict_to_newish_commits(void)
{
	git_blame_options opts = GIT_BLAME_OPTIONS_INIT;

	cl_git_pass(git_repository_open(&g_repo, cl_fixture("testrepo.git")));

	{
		git_object *obj;
		cl_git_pass(git_revparse_single(&obj, g_repo, "be3563a"));
		git_oid_cpy(&opts.oldest_commit, git_object_id(obj));
		git_object_free(obj);
	}

	cl_git_pass(git_blame_file(&g_blame, g_repo, "branch_file.txt", &opts));

	cl_assert_equal_i(2, git_blame_get_hunk_count(g_blame));
	check_blame_hunk_index(g_repo, g_blame, 0,  1, 1, 1, "be3563a", "branch_file.txt");
	check_blame_hunk_index(g_repo, g_blame, 1,  2, 1, 0, "a65fedf", "branch_file.txt");
}
