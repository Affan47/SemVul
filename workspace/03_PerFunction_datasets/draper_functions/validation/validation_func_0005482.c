gpk_prefs_model_get_iter (GpkPrefsPrivate *priv, GtkTreeModel *model, GtkTreeIter *iter, const gchar *id)
{
	gboolean ret = TRUE;
	priv->id_tmp = id;
	priv->path_tmp = NULL;
	gtk_tree_model_foreach (model, (GtkTreeModelForeachFunc) gpk_prefs_find_iter_model_cb, priv);
	if (priv->path_tmp == NULL) {
		gtk_list_store_append (GTK_LIST_STORE(model), iter);
	} else {
		ret = gtk_tree_model_get_iter (model, iter, priv->path_tmp);
		gtk_tree_path_free (priv->path_tmp);
	}
	return ret;
}
