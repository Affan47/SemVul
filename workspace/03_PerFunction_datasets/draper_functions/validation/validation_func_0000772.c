test_config_stress__escape_subsection_names(void)
{
	git_config *config;
	const char *str;

	cl_assert(git_path_exists("git-test-config"));
	cl_git_pass(git_config_open_ondisk(&config, TEST_CONFIG));

	cl_git_pass(git_config_set_string(config, "some.sec\\tion.other", "foo"));
	git_config_free(config);

	cl_git_pass(git_config_open_ondisk(&config, TEST_CONFIG));

	cl_git_pass(git_config_get_string(&str, config, "some.sec\\tion.other"));
	cl_assert(!strcmp("foo", str));
	git_config_free(config);
}
