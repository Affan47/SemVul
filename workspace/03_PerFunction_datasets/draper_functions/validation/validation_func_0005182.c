saving_thread_func(gpointer data)
{
	GTimeVal interval;
	GMutex *m = g_mutex_new();
	do
	{
		g_mutex_lock(change_config_mutex);

		if (
			panel_config_changed ||
			(debug_config_changed && DEBUG_STORE_PLUGIN == dstore)
		)
		{
			gchar *config_data;


			if (debug_config_changed)
			{
				save_to_keyfile(keyfile_plugin);
				debug_config_changed = FALSE;
			}

			config_data = g_key_file_to_data(keyfile_plugin, NULL, NULL);
			g_file_set_contents(plugin_config_path, config_data, -1, NULL);
			g_free(config_data);

			panel_config_changed = FALSE;
		}

		if (debug_config_changed && DEBUG_STORE_PROJECT == dstore)
		{
			gchar *config_data;


			save_to_keyfile(keyfile_project);

			config_data = g_key_file_to_data(keyfile_project, NULL, NULL);
			g_file_set_contents(geany_data->app->project->file_name, config_data, -1, NULL);
			g_free(config_data);

			debug_config_changed = FALSE;
		}

		g_mutex_unlock(change_config_mutex);

		g_get_current_time(&interval);
		g_time_val_add(&interval, SAVING_INTERVAL);
	}
	while (!g_cond_timed_wait(cond, m, &interval));
	g_mutex_free(m);

	return NULL;
}
