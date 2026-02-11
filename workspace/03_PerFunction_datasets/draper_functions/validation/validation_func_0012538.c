s_create_module_prefs_list(void)
{
	const LList *plugins = GetPref(EB_PLUGIN_LIST);
	LList *module_prefs_list = NULL;

	for (; plugins; plugins = plugins->next) {
		const eb_PLUGIN_INFO *plugin_info = plugins->data;
		t_module_pref *pref_info = NULL;

		if (plugin_info == NULL)
			continue;

		pref_info = calloc(1, sizeof(t_module_pref));

		s_fill_in_module_pref_info(pref_info, plugin_info);

		module_prefs_list = l_list_append(module_prefs_list, pref_info);
	}

	return (l_list_nth(module_prefs_list, 0));
}
