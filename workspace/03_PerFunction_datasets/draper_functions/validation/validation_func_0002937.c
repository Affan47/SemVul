test_refs_reflog_reflog__renaming_the_reference_moves_the_reflog(void)
{
	git_reference *master, *new_master;
	git_buf master_log_path = GIT_BUF_INIT, moved_log_path = GIT_BUF_INIT;

	git_buf_joinpath(&master_log_path, git_repository_path(g_repo), GIT_REFLOG_DIR);
	git_buf_puts(&moved_log_path, git_buf_cstr(&master_log_path));
	git_buf_joinpath(&master_log_path, git_buf_cstr(&master_log_path), "refs/heads/master");
	git_buf_joinpath(&moved_log_path, git_buf_cstr(&moved_log_path), "refs/moved");

	cl_assert_equal_i(true, git_path_isfile(git_buf_cstr(&master_log_path)));
	cl_assert_equal_i(false, git_path_isfile(git_buf_cstr(&moved_log_path)));

	cl_git_pass(git_reference_lookup(&master, g_repo, "refs/heads/master"));
	cl_git_pass(git_reference_rename(&new_master, master, "refs/moved", 0));
	git_reference_free(master);

	cl_assert_equal_i(false, git_path_isfile(git_buf_cstr(&master_log_path)));
	cl_assert_equal_i(true, git_path_isfile(git_buf_cstr(&moved_log_path)));

	git_reference_free(new_master);
	git_buf_free(&moved_log_path);
	git_buf_free(&master_log_path);
}
