load_proc_config(gchar *arg)
	{
	gchar	config[32], name[16], item[CFG_BUFSIZE], item1[CFG_BUFSIZE];
	gint	n;

	n = sscanf(arg, "%31s %[^\n]", config, item);
	if (n == 2)
		{
		if (!strcmp(config, "enable"))
			sscanf(item, "%d %d\n", &proc.enabled, &proc.extra_info);
		else if (!strcmp(config, "launch"))
			proc_launch.command = g_strdup(item);
		else if (!strcmp(config, "tooltip_comment"))
			proc_launch.tooltip_comment = g_strdup(item);
		else if (!strcmp(config, "sensor_mode"))
			sscanf(item, "%d\n", &sensor_separate_mode);
		else if (!strcmp(config, "text_format"))
			{
			gkrellm_locale_dup_string(&text_format, item, &text_format_locale);
			new_text_format = TRUE;
			}
		else if (!strcmp(config, GKRELLM_CHARTCONFIG_KEYWORD))
			gkrellm_load_chartconfig(&proc.chart_config, item, 2);
		else if (!strcmp(config, GKRELLM_ALERTCONFIG_KEYWORD))
			{
			if (sscanf(item, "%15s %[^\n]", name, item1) == 2)
				{
				if (!strcmp(name, "load"))
					{
					if (!load_alert)
						create_load_alert();
					gkrellm_load_alertconfig(&load_alert, item1);
					}
				else if (!strcmp(name, "users"))
					{
					if (!users_alert)
						create_users_alert();
					gkrellm_load_alertconfig(&users_alert, item1);
					}
				else if (!strcmp(name, "processes"))
					{
					if (!processes_alert)
						create_processes_alert();
					gkrellm_load_alertconfig(&processes_alert, item1);
					}
				}
			}
		}
	}
