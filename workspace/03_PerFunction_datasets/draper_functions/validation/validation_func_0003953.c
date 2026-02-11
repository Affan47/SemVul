inf_gtk_browser_view_sync_added(InfGtkBrowserView* view,
                                InfcBrowser* browser,
                                InfcSessionProxy* proxy,
                                GtkTreePath* path,
                                GtkTreeIter* iter)
{
  InfGtkBrowserViewPrivate* priv;
  InfGtkBrowserViewBrowser* view_browser;
  InfSession* session;
  InfGtkBrowserViewSync* sync;

  priv = INF_GTK_BROWSER_VIEW_PRIVATE(view);
  session = infc_session_proxy_get_session(proxy);

  view_browser = inf_gtk_browser_view_find_view_browser(view, browser);
  g_assert(view_browser != NULL);

  g_assert(inf_gtk_browser_view_find_sync(view, view_browser, proxy) == NULL);
  g_assert(
    inf_session_get_synchronization_status(
      session,
      infc_browser_get_connection(browser)
    ) != INF_SESSION_SYNC_NONE
  );

  sync = g_slice_new(InfGtkBrowserViewSync);
  sync->view_browser = view_browser;
  sync->proxy = proxy;
  g_object_ref(proxy);

  sync->reference = gtk_tree_row_reference_new_proxy(
    G_OBJECT(priv->column),
    gtk_tree_view_get_model(GTK_TREE_VIEW(view)),
    path
  );

  g_assert(sync->reference != NULL);
  view_browser->syncs = g_slist_prepend(view_browser->syncs, sync);

  g_signal_connect_after(
    G_OBJECT(session),
    "synchronization-progress",
    G_CALLBACK(inf_gtk_browser_view_session_synchronization_progress_cb),
    sync
  );

  g_signal_connect_after(
    G_OBJECT(session),
    "synchronization-complete",
    G_CALLBACK(inf_gtk_browser_view_session_synchronization_complete_cb),
    sync
  );

  g_signal_connect_after(
    G_OBJECT(session),
    "synchronization-failed",
    G_CALLBACK(inf_gtk_browser_view_session_synchronization_failed_cb),
    sync
  );

  inf_gtk_browser_view_redraw_row(view, path, iter);
}
