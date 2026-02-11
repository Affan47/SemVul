on_menu_pl_remove_crop_activate(GtkWidget *widget, gpointer data) {
  GtkWidget *tv;
  GtkTreeModel *tm;
  GtkTreeSelection *ts;
  GtkTreeIter iter;
  gint i = 0, id;

  if(!mpd_check_connected(glurp->mpd)) return FALSE;

  tv = GTK_WIDGET(gtk_builder_get_object(builder, "treeview_playlist"));
  tm = gtk_tree_view_get_model(GTK_TREE_VIEW(tv));
  ts = gtk_tree_view_get_selection(GTK_TREE_VIEW(tv));

  if( !gtk_tree_model_get_iter_first(tm, &iter) ) {
    debug("Couldn't get first iter, playlist empty?");
    return FALSE;
  }

  do {
    if( !gtk_tree_selection_iter_is_selected(ts, &iter) ) {
      gtk_tree_model_get(tm, &iter, PL_ID, &id, -1);
      mpd_playlist_queue_delete_id( glurp->mpd, id);
    }
    else i++;
  } while( gtk_tree_model_iter_next(tm, &iter) );

  mpd_playlist_queue_commit(glurp->mpd);

  return FALSE;
}
