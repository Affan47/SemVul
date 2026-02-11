fpm_clear_list()
{
  GList *list;
  GtkTreeModel *list_store;

  list = g_list_first(glb_pass_list);
  while (list != NULL)
  {
    g_free(list->data);
    list = g_list_next(list);
  }
  g_list_free(glb_pass_list);
  glb_pass_list = NULL;

  list_store = gtk_tree_view_get_model(gui->main_clist);
  gtk_list_store_clear(GTK_LIST_STORE(list_store));
}
