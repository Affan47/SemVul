update_ignore_space_arg()
{
	if (opt_ignore_space == IGNORE_SPACE_ALL) {
		string_copy(opt_ignore_space_arg, "--ignore-all-space");
	} else if (opt_ignore_space == IGNORE_SPACE_SOME) {
		string_copy(opt_ignore_space_arg, "--ignore-space-change");
	} else if (opt_ignore_space == IGNORE_SPACE_AT_EOL) {
		string_copy(opt_ignore_space_arg, "--ignore-space-at-eol");
	} else {
		string_copy(opt_ignore_space_arg, "");
	}
}
