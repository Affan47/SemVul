book_view_gtk_dispose (GObject *obj)
{
  BookViewGtk *view = NULL;

  view = BOOK_VIEW_GTK (obj);

  for (std::list<boost::signals::connection>::iterator iter
	 = view->priv->connections.begin ();
       iter != view->priv->connections.end ();
       ++iter)
    iter->disconnect ();

  if (view->priv->tree_view) {

    g_signal_handlers_disconnect_matched (gtk_tree_view_get_selection (view->priv->tree_view),
					  (GSignalMatchType) G_SIGNAL_MATCH_DATA,
					  0,
					  (GQuark) 0,
					  NULL,
					  NULL,
					  view);
    gtk_list_store_clear (GTK_LIST_STORE (gtk_tree_view_get_model (view->priv->tree_view)));

    view->priv->tree_view = NULL;
  }

  G_OBJECT_CLASS (book_view_gtk_parent_class)->dispose (obj);
}
