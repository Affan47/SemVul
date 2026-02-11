load_plugins_enable_file(void)
	{
	FILE	*f;
	gchar	*path, *s, buf[256];

	gkrellm_free_glist_and_data(&plugins_enable_list);
	path = gkrellm_make_config_file_name(gkrellm_homedir(),PLUGIN_ENABLE_FILE);
	if ((f = g_fopen(path, "r")) != NULL)
		{
		while ((fgets(buf, sizeof(buf), f)) != NULL)
			{
			if ((s = strchr(buf, '\n')) != NULL)
				*s = '\0';
			if (!buf[0])
				continue;
			s = g_path_get_basename(buf);
			plugins_enable_list = g_list_append(plugins_enable_list, s);
			}
		fclose(f);
		}
	g_free(path);
	}
