nemo_properties_window_present (GList       *original_files,
				    GtkWidget   *parent_widget,
				    const gchar *startup_id)
{
	GList *l, *next;
	GtkWidget *parent_window;
	StartupData *startup_data;
	GList *target_files;
	GtkWindow *existing_window;
	char *pending_key;

	g_return_if_fail (original_files != NULL);
	g_return_if_fail (parent_widget == NULL || GTK_IS_WIDGET (parent_widget));


	if (windows == NULL) {
		windows = g_hash_table_new (NULL, NULL);
	}

	if (pending_lists == NULL) {
		pending_lists = g_hash_table_new (g_str_hash, g_str_equal);
	}


	existing_window = get_existing_window (original_files);
	if (existing_window != NULL) {
		if (parent_widget)
			gtk_window_set_screen (existing_window,
					       gtk_widget_get_screen (parent_widget));
		else if (startup_id)
			gtk_window_set_startup_id (existing_window, startup_id);

		gtk_window_present (existing_window);
		return;
	}


	pending_key = get_pending_key (original_files);


	if (g_hash_table_lookup (pending_lists, pending_key) != NULL) {
		return;
	}

	target_files = get_target_file_list (original_files);

	startup_data = startup_data_new (original_files,
					 target_files,
					 pending_key,
					 parent_widget,
					 startup_id);

	nemo_file_list_free (target_files);
	g_free(pending_key);


	g_hash_table_insert (pending_lists, startup_data->pending_key, startup_data->pending_key);
	if (parent_widget) {
		g_signal_connect (parent_widget, "destroy",
				  G_CALLBACK (parent_widget_destroyed_callback), startup_data);

		parent_window = gtk_widget_get_ancestor (parent_widget, GTK_TYPE_WINDOW);
	} else
		parent_window = NULL;

	eel_timed_wait_start
		(cancel_create_properties_window_callback,
		 startup_data,
		 _("Creating Properties window."),
		 parent_window == NULL ? NULL : GTK_WINDOW (parent_window));

	for (l = startup_data->target_files; l != NULL; l = next) {
		next = l->next;
		nemo_file_call_when_ready
			(NEMO_FILE (l->data),
			 NEMO_FILE_ATTRIBUTE_INFO,
			 is_directory_ready_callback,
			 startup_data);
	}
}
