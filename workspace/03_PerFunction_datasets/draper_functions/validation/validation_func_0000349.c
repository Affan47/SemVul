test_stress_diff__rename_big_files(void)
{
	git_index *index;
	char tmp[64];
	int i, j;
	git_buf b = GIT_BUF_INIT;

	g_repo = cl_git_sandbox_init("renames");

	cl_git_pass(git_repository_index(&index, g_repo));

	for (i = 0; i < 100; i += 1) {
		p_snprintf(tmp, sizeof(tmp), "renames/newfile%03d", i);
		for (j = i * 256; j > 0; --j)
			git_buf_printf(&b, "more content %d\n", i);
		cl_git_mkfile(tmp, b.ptr);
	}

	for (i = 0; i < 100; i += 1) {
		p_snprintf(tmp, sizeof(tmp), "renames/newfile%03d", i);
		cl_git_pass(git_index_add_bypath(index, tmp + strlen("renames/")));
	}

	git_buf_free(&b);
	git_index_free(index);

	test_with_many(100);
}
