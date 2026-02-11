get_value(const char* key_, const char* regex_)
{
	int ret = -1;
	char *tl;
	char *global = NULL, *repo_config = NULL;
	const char *system_wide = NULL, *local;

	local = getenv(CONFIG_ENVIRONMENT);
	if (!local) {
		const char *home = getenv("HOME");
		local = getenv(CONFIG_LOCAL_ENVIRONMENT);
		if (!local)
			local = repo_config = xstrdup(git_path("config"));
		if (home)
			global = xstrdup(mkpath("%s/.gitconfig", home));
		system_wide = ETC_GITCONFIG;
	}

	key = xstrdup(key_);
	for (tl=key+strlen(key)-1; tl >= key && *tl != '.'; --tl)
		*tl = tolower(*tl);
	for (tl=key; *tl && *tl != '.'; ++tl)
		*tl = tolower(*tl);

	if (use_key_regexp) {
		key_regexp = (regex_t*)xmalloc(sizeof(regex_t));
		if (regcomp(key_regexp, key, REG_EXTENDED)) {
			fprintf(stderr, "Invalid key pattern: %s\n", key_);
			goto free_strings;
		}
	}

	if (regex_) {
		if (regex_[0] == '!') {
			do_not_match = 1;
			regex_++;
		}

		regexp = (regex_t*)xmalloc(sizeof(regex_t));
		if (regcomp(regexp, regex_, REG_EXTENDED)) {
			fprintf(stderr, "Invalid pattern: %s\n", regex_);
			goto free_strings;
		}
	}

	if (do_all && system_wide)
		git_config_from_file(show_config, system_wide);
	if (do_all && global)
		git_config_from_file(show_config, global);
	git_config_from_file(show_config, local);
	if (!do_all && !seen && global)
		git_config_from_file(show_config, global);
	if (!do_all && !seen && system_wide)
		git_config_from_file(show_config, system_wide);

	free(key);
	if (regexp) {
		regfree(regexp);
		free(regexp);
	}

	if (do_all)
		ret = !seen;
	else
		ret = (seen == 1) ? 0 : seen > 1 ? 2 : 1;

free_strings:
	free(repo_config);
	free(global);
	return ret;
}
