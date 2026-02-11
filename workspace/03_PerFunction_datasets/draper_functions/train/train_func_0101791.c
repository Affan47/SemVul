git_diff_ui_config(const char *var, const char *value)
{
	if (!strcmp(var, "diff.renamelimit")) {
		diff_rename_limit_default = git_config_int(var, value);
		return 0;
	}
	if (!strcmp(var, "diff.color") || !strcmp(var, "color.diff")) {
		diff_use_color_default = git_config_colorbool(var, value);
		return 0;
	}
	if (!strcmp(var, "diff.renames")) {
		if (!value)
			diff_detect_rename_default = DIFF_DETECT_RENAME;
		else if (!strcasecmp(value, "copies") ||
			 !strcasecmp(value, "copy"))
			diff_detect_rename_default = DIFF_DETECT_COPY;
		else if (git_config_bool(var,value))
			diff_detect_rename_default = DIFF_DETECT_RENAME;
		return 0;
	}
	if (!prefixcmp(var, "diff.")) {
		const char *ep = strrchr(var, '.');

		if (ep != var + 4 && !strcmp(ep, ".command"))
			return parse_lldiff_command(var, ep, value);
	}
	if (!prefixcmp(var, "diff.color.") || !prefixcmp(var, "color.diff.")) {
		int slot = parse_diff_color_slot(var, 11);
		color_parse(value, var, diff_colors[slot]);
		return 0;
	}

	return git_default_config(var, value);
}
