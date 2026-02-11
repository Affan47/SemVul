on_diff_selected_column_toggled (GtkCellRendererToggle *renderer,
								 gchar *tree_path,
								 LogData *data)
{
	GtkTreeIter iter;
	glong revision;
	GtkWidget *log_diff_selected_button;
	gboolean selected;

	gtk_tree_model_get_iter_from_string (GTK_TREE_MODEL (data->log_store),
										&iter, tree_path);
	gtk_tree_model_get (GTK_TREE_MODEL (data->log_store), &iter,
						COL_DIFF_SELECTED, &selected,
						COL_REVISION, &revision,
						-1);

	log_diff_selected_button = GTK_WIDGET (gtk_builder_get_object (data->bxml,
													 "log_diff_selected_button"));

	selected = !selected;

	if (selected)
	{

		if (g_hash_table_size (data->selected_diff_revisions) < 2)
		{
			g_hash_table_insert (data->selected_diff_revisions,
							 	 GINT_TO_POINTER (revision), NULL);

			gtk_list_store_set (data->log_store, &iter,
								COL_DIFF_SELECTED, TRUE,
								-1);
		}
	}
	else
	{
		g_hash_table_remove (data->selected_diff_revisions,
							 GINT_TO_POINTER (revision));

		gtk_list_store_set (data->log_store, &iter,
							COL_DIFF_SELECTED, FALSE,
							-1);
	}


	gtk_widget_set_sensitive (log_diff_selected_button,
							  g_hash_table_size (data->selected_diff_revisions) == 2);

}
