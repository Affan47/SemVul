book_tree_find_uri_foreach (GtkTreeModel *model,
			    GtkTreePath  *path,
			    GtkTreeIter  *iter,
			    FindURIData  *data)
{
	DhLink      *link;
        gchar       *link_uri;

	gtk_tree_model_get (model, iter,
			    COL_LINK, &link,
			    -1);

        link_uri = dh_link_get_uri (link);
	if (g_str_has_prefix (data->uri, link_uri)) {
		data->found = TRUE;
		data->iter = *iter;
		data->path = gtk_tree_path_copy (path);
	}
        g_free (link_uri);

	return data->found;
}
