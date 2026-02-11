row_emit_changed(GtkTreeModel *model, const DirRow2 *row)
{
	GtkTreePath	*path;

	if((path = gtk_tree_model_get_path(model, (GtkTreeIter *) row)) != NULL)
	{
		gtk_tree_model_row_changed(model, path, (GtkTreeIter *) row);
		gtk_tree_path_free(path);
	}
}
