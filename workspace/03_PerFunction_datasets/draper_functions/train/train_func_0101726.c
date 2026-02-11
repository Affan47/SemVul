git_default_config(const char *var, const char *value, void *dummy)
{
	if (!prefixcmp(var, "core."))
		return git_default_core_config(var, value);

	if (!prefixcmp(var, "user."))
		return git_default_user_config(var, value);

	if (!prefixcmp(var, "i18n."))
		return git_default_i18n_config(var, value);

	if (!prefixcmp(var, "branch."))
		return git_default_branch_config(var, value);

	if (!prefixcmp(var, "push."))
		return git_default_push_config(var, value);

	if (!prefixcmp(var, "mailmap."))
		return git_default_mailmap_config(var, value);

	if (!prefixcmp(var, "advice."))
		return git_default_advice_config(var, value);

	if (!strcmp(var, "pager.color") || !strcmp(var, "color.pager")) {
		pager_use_color = git_config_bool(var,value);
		return 0;
	}


	return 0;
}
