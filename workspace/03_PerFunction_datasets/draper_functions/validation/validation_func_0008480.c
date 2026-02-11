sdb_model_iter_unref (GtkTreeModel *tree_model, GtkTreeIter  *iter)
{
	SymbolDBModelNode *parent_node;
	gint child_offset;

	g_return_if_fail (sdb_model_iter_is_valid (tree_model, iter));

	parent_node = (SymbolDBModelNode*) iter->user_data;
	child_offset = GPOINTER_TO_INT (iter->user_data2);

	sdb_model_node_unref_child (parent_node, child_offset);
}
