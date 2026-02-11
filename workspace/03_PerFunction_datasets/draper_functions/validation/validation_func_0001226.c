world_tree_activate(graph_view_handle view)
{
  GtkTreeIter iter;

  if (find_view(view, &iter))
  {
    gtk_tree_selection_select_iter(gtk_tree_view_get_selection(GTK_TREE_VIEW(g_world_tree_widget)), &iter);
  }
}
