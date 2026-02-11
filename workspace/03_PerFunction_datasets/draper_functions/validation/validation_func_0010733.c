totem_playlist_save_iter_foreach (GtkTreeModel *model,
				  GtkTreePath  *path,
				  GtkTreeIter  *iter,
				  gpointer      user_data)
{
	TotemPlPlaylist *playlist = user_data;
	TotemPlPlaylistIter pl_iter;
	gchar *uri, *title;
	gboolean custom_title;

	gtk_tree_model_get (model, iter,
			    URI_COL, &uri,
			    FILENAME_COL, &title,
			    TITLE_CUSTOM_COL, &custom_title,
			    -1);

	totem_pl_playlist_append (playlist, &pl_iter);
	totem_pl_playlist_set (playlist, &pl_iter,
			       TOTEM_PL_PARSER_FIELD_URI, uri,
			       TOTEM_PL_PARSER_FIELD_TITLE, (custom_title) ? title : NULL,
			       NULL);

	g_free (uri);
	g_free (title);

	return FALSE;
}
