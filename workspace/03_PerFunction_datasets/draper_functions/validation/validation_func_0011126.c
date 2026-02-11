remove_blood_pressed_cb(GtkButton * button, gpointer data) {

  tb_fads_t * tb_fads = data;
  GtkTreeIter iter;
  GtkTreeSelection * selection;
  GtkTreeModel * model;

  selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (tb_fads->blood_tree));

  if(gtk_tree_selection_get_selected(selection, &model, &iter)) {
    gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
  }

  return;
}
