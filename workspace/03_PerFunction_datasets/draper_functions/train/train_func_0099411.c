config_length(GKeyFile *config, const gchar *section, const gchar *name)
{
	gchar *key;
	gint i = 0;

	key = g_strdup_printf("%s%d", name, i);
	while (g_key_file_has_key(config, section, key, NULL))
	{
		i++;
		g_free(key);
		key = g_strdup_printf("%s%d", name, i);
	}
	g_free(key);
	return i;
}
