git_config_colorbool(const char *var, const char *value)
{
	if (!value)
		return 1;
	if (!strcasecmp(value, "auto")) {
		if (isatty(1) || (pager_in_use && pager_use_color)) {
			char *term = getenv("TERM");
			if (term && strcmp(term, "dumb"))
				return 1;
		}
		return 0;
	}
	if (!strcasecmp(value, "never"))
		return 0;
	if (!strcasecmp(value, "always"))
		return 1;
	return git_config_bool(var, value);
}
