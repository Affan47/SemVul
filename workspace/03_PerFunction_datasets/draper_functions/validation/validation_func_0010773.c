collection_table_find_iter(CollectTable *ct, CollectInfo *info, GtkTreeIter *iter, gint *column)
{
	GtkTreeModel *store;
	gint row, col;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(ct->listview));
	if (!collection_table_find_position(ct, info, &row, &col)) return FALSE;
	if (!gtk_tree_model_iter_nth_child(store, iter, NULL, row)) return FALSE;
	if (column) *column = col;

	return TRUE;
}
