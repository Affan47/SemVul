worklists_response(GtkWidget *w, gint response)
{
  struct global_worklist *pgwl;
  int id;
  GtkTreeSelection *selection;
  GtkTreeModel *model;
  GtkTreeIter it;

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(worklists_list));

  if (gtk_tree_selection_get_selected(selection, &model, &it)) {
    gtk_tree_model_get(model, &it, 1, &id, -1);
    pgwl = global_worklist_by_id(id);
  } else {
    pgwl = NULL;
    id = -1;
  }

  switch (response) {
  case WORKLISTS_NEW:
    global_worklist_new(_("new"));
    update_worklist_report_dialog();
    return;

  case WORKLISTS_DELETE:
    if (!pgwl) {
      return;
    }

    popdown_worklist(pgwl);
    global_worklist_destroy(pgwl);
    update_worklist_report_dialog();
    return;

  case WORKLISTS_PROPERTIES:
    if (!pgwl) {
      return;
    }

    popup_worklist(pgwl);
    return;

  default:
    gtk_widget_destroy(worklists_shell);
    return;
  }
}
