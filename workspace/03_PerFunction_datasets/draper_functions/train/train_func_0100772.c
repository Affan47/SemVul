inf_gtk_browser_view_get_selected(InfGtkBrowserView* view,
                                  GtkTreeIter* iter)
{
  GtkTreeSelection* selection;

  g_return_val_if_fail(INF_GTK_IS_BROWSER_VIEW(view), FALSE);

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
  return gtk_tree_selection_get_selected(selection, NULL, iter);
}
