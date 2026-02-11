delete_line(AoBookmarkList *bm, gint line_nr)
{
	AoBookmarkListPrivate *priv = AO_BOOKMARK_LIST_GET_PRIVATE(bm);

	priv->search_line = line_nr + 1;
	priv->search_iter = NULL;
	gtk_tree_model_foreach(GTK_TREE_MODEL(priv->store), tree_model_foreach, bm);
	if (priv->search_iter != NULL)
	{
		gtk_list_store_remove(priv->store, priv->search_iter);
		gtk_tree_iter_free(priv->search_iter);
	}
}
