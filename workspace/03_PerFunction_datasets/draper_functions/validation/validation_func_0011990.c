gns_get_iter (GtkTreeModel *model, GtkTreeIter *iter, GtkTreePath *path)
{
	GtkSharpNodeStore *store = (GtkSharpNodeStore *) model;
	gint node_idx;

	if (!store->tree_model.get_node (&node_idx, path))
		return FALSE;

	iter->stamp = store->stamp;
	iter->user_data = GINT_TO_POINTER (node_idx);
	return TRUE;
}
