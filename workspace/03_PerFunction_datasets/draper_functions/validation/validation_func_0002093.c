glade_project_model_iter_n_children (GtkTreeModel* model,
                                     GtkTreeIter* iter)
{
	GladeProject* project = GLADE_PROJECT (model);

	g_return_val_if_fail (iter == NULL || VALID_ITER (project, iter), 0);

	if (iter)
	{
		GladeWidget *widget = glade_widget_get_from_gobject (iter->user_data);

		return glade_project_count_children (project, widget);
	}

	return g_list_length (project->priv->tree);
}
