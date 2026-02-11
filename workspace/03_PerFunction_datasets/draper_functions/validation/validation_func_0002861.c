gpk_update_viewer_update_global_state_recursive (GtkTreeModel *model, GtkTreeIter *iter)
{
	gboolean selected;
	PkRestartEnum restart;
	guint size;
	gchar *package_id = NULL;
	gboolean child_valid;
	GtkTreeIter child_iter;

	gtk_tree_model_get (model, iter,
			    GPK_UPDATES_COLUMN_SELECT, &selected,
			    GPK_UPDATES_COLUMN_RESTART, &restart,
			    GPK_UPDATES_COLUMN_SIZE, &size,
			    GPK_UPDATES_COLUMN_ID, &package_id,
			    -1);
	if (selected && package_id != NULL) {
		size_total += size;
		number_total++;
		if (restart > restart_worst)
			restart_worst = restart;
	}


	child_valid = gtk_tree_model_iter_children (model, &child_iter, iter);
	while (child_valid) {
		gpk_update_viewer_update_global_state_recursive (model, &child_iter);
		child_valid = gtk_tree_model_iter_next (model, &child_iter);
	}
	g_free (package_id);
}
