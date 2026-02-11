parse_args(int argc, const char **argv)
{
	const char * const * usage_str = revert_or_cherry_pick_usage();
	int noop;
	struct option options[] = {
		OPT_BOOLEAN('n', "no-commit", &no_commit, "don't automatically commit"),
		OPT_BOOLEAN('e', "edit", &edit, "edit the commit message"),
		{ OPTION_BOOLEAN, 'r', NULL, &noop, NULL, "no-op (backward compatibility)",
		  PARSE_OPT_NOARG | PARSE_OPT_HIDDEN, NULL, 0 },
		OPT_BOOLEAN('s', "signoff", &signoff, "add Signed-off-by:"),
		OPT_INTEGER('m', "mainline", &mainline, "parent number"),
		OPT_RERERE_AUTOUPDATE(&allow_rerere_auto),
		OPT_STRING(0, "strategy", &strategy, "strategy", "merge strategy"),
		OPT_CALLBACK('X', "strategy-option", &xopts, "option",
			"option for merge strategy", option_parse_x),
		OPT_END(),
		OPT_END(),
		OPT_END(),
	};

	if (action == CHERRY_PICK) {
		struct option cp_extra[] = {
			OPT_BOOLEAN('x', NULL, &no_replay, "append commit name"),
			OPT_BOOLEAN(0, "ff", &allow_ff, "allow fast-forward"),
			OPT_END(),
		};
		if (parse_options_concat(options, ARRAY_SIZE(options), cp_extra))
			die(_("program error"));
	}

	commit_argc = parse_options(argc, argv, NULL, options, usage_str,
				    PARSE_OPT_KEEP_ARGV0 |
				    PARSE_OPT_KEEP_UNKNOWN);
	if (commit_argc < 2)
		usage_with_options(usage_str, options);

	commit_argv = argv;
}
