test_refs_reflog_reflog__reading_the_reflog_from_a_reference_with_no_log_returns_an_empty_one(void)
{
	git_reference *subtrees;
	git_reflog *reflog;
	git_buf subtrees_log_path = GIT_BUF_INIT;

	cl_git_pass(git_reference_lookup(&subtrees, g_repo, "refs/heads/subtrees"));

	git_buf_join_n(&subtrees_log_path, '/', 3, git_repository_path(g_repo), GIT_REFLOG_DIR, git_reference_name(subtrees));
	cl_assert_equal_i(false, git_path_isfile(git_buf_cstr(&subtrees_log_path)));

	cl_git_pass(git_reflog_read(&reflog, subtrees));

	cl_assert_equal_i(0, (int)git_reflog_entrycount(reflog));

	git_reflog_free(reflog);
	git_reference_free(subtrees);
	git_buf_free(&subtrees_log_path);
}
