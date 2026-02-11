filter_options(const char *argv[], bool blame)
{
	filter_rev_parse(&opt_file_argv, "--no-revs", "--no-flags", argv);

	if (blame)
		filter_rev_parse(&opt_blame_argv, "--no-revs", "--flags", argv);
	else
		filter_rev_parse(&opt_diff_argv, "--no-revs", "--flags", argv);

	filter_rev_parse(&opt_rev_argv, "--symbolic", "--revs-only", argv);
}
