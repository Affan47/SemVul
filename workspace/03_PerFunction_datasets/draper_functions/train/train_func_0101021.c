play_cb (GtkWidget* widget, gpointer data)
{
  GtkTreeIter iter;

  if (gtk_tree_selection_get_selected (sel, NULL, &iter))
  {
    GtkTreePath *path = gtk_tree_model_get_path (pl_model, &iter);
    playlist_play (gtk_tree_path_get_indices (path)[0]);
    gtk_tree_path_free (path);
  }
}
