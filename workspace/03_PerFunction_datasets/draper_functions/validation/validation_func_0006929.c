config_get_command(const gchar * lang, gint cmd_num, gboolean * intern)
{
	gchar *ret, *tmp;
	gchar *key = g_strdup_printf("command%d", cmd_num);
	ret = utils_get_setting_string(config, lang, key, "");
	g_free(key);
	if (!NZV(ret))
		return ret;
	key = g_strdup_printf("command%d", cmd_num + 1);
	tmp = utils_get_setting_string(config, lang, key, "");
	g_free(key);
	if (NZV(tmp))
		*intern = TRUE;
	else
		*intern = utils_get_setting_boolean(config, lang, "internal", FALSE);
	g_free(tmp);
	return ret;
}
