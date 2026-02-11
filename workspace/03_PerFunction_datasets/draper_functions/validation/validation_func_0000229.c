on_library_dialog_edit_clicked         (GtkButton       *button,
                                        SpiceLibrary  *spicelib)
{
  GtkTreeView *treeview;
  GtkTreeIter iter;
  GtkTreeModel *model;
  GtkTreeSelection *selection;
  gchar *libname, *buf;

  treeview = GTK_TREE_VIEW(lookup_widget(spicelib->dialog, "treeview1"));
  model = gtk_tree_view_get_model(treeview);
  selection = gtk_tree_view_get_selection(treeview);

  if (gtk_tree_selection_get_selected (selection, NULL, &iter)) {
    gtk_tree_model_get(model, &iter,
		       0, &libname,
		       -1);
    buf=g_strdup_printf("%s %s &", easyspice->commands->editor, libname);
    if (VERBOSE1)
      printf("executing: \"%s\"\n",buf);
    system(buf);
    g_free(libname);
    g_free(buf);
  }
}
