search_files_replace_clicked (SearchFiles* sf)
{
	GtkTreeIter iter;

	if (gtk_tree_model_get_iter_first(sf->priv->files_model, &iter))
	{
		AnjutaCommandQueue* queue = anjuta_command_queue_new(ANJUTA_COMMAND_QUEUE_EXECUTE_MANUAL);
		const gchar* pattern =
			gtk_entry_get_text (GTK_ENTRY (sf->priv->search_entry));
		const gchar* replace =
			gtk_entry_get_text (GTK_ENTRY (sf->priv->replace_entry));
		do
		{
			GFile* file;
			gboolean selected;


			sf->priv->regex =
				gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (sf->priv->regex_check));
			sf->priv->case_sensitive =
				gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (sf->priv->case_check));

			g_free (sf->priv->last_search_string);
			sf->priv->last_search_string = g_strdup(pattern);
			g_free (sf->priv->last_replace_string);
			sf->priv->last_replace_string = g_strdup(replace);

			gtk_tree_model_get (sf->priv->files_model, &iter,
			                    COLUMN_FILE, &file,
			                    COLUMN_SELECTED, &selected, -1);
			if (selected)
			{
				GtkTreePath* path;
				GtkTreeRowReference* ref;

				path = gtk_tree_model_get_path(sf->priv->files_model, &iter);
				ref = gtk_tree_row_reference_new(sf->priv->files_model,
				                                 path);
				gtk_tree_path_free(path);


				SearchFileCommand* cmd = search_file_command_new(file,
				                                                 pattern,
				                                                 replace,
				                                                 sf->priv->case_sensitive,
				                                                 sf->priv->regex);
				g_object_set_data (G_OBJECT (cmd), "__tree_ref",
				                   ref);

				g_signal_connect (cmd, "command-finished",
				                  G_CALLBACK(search_files_command_finished), sf);

				anjuta_command_queue_push(queue,
				                          ANJUTA_COMMAND(cmd));
			}
			g_object_unref (file);
		}
		while (gtk_tree_model_iter_next(sf->priv->files_model, &iter));

		g_signal_connect_swapped (queue, "finished", G_CALLBACK (search_files_finished), sf);

		anjuta_command_queue_start (queue);
		gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE (sf->priv->files_model),
		                                     COLUMN_COUNT,
		                                     GTK_SORT_DESCENDING);

		sf->priv->busy = TRUE;
		search_files_update_ui(sf);
	}
}
