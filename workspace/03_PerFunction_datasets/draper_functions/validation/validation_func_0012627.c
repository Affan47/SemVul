cmd_whatchanged(int argc, const char **argv, const char *prefix)
{
	struct rev_info rev;

	git_config(git_log_config, NULL);

	if (diff_use_color_default == -1)
		diff_use_color_default = git_use_color_default;

	init_revisions(&rev, prefix);
	rev.diff = 1;
	rev.simplify_history = 0;
	cmd_log_init(argc, argv, prefix, &rev);
	if (!rev.diffopt.output_format)
		rev.diffopt.output_format = DIFF_FORMAT_RAW;
	return cmd_log_walk(&rev);
}
