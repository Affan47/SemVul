gkrellm_client_plugin_get_setup(gchar *key_name,
				void (*setup_func_cb)(gchar *str))
	{
	GList	*list;
	gchar	*line, *s;
	gint	n;

	if (!_GK.client_mode || !key_name || !setup_func_cb)
		return;
	for (list = client_plugin_setup_line_list; list; list = list->next)
		{
		line = (gchar *) list->data;
		n = strlen(key_name);
		s = line + n;
		if (!strncmp(line, key_name, n) && *s == ' ')
			{
			while (*s == ' ')
				++s;
			(*setup_func_cb)(s);
			}
		}
	}
