we_guied_plugin_filter_func(GtkTreeModel *model,
                            GtkTreeIter  *iter,
                            gpointer      data)
{
  World    *world = (World *) data;
  gpointer  object;

  if (world->show_plugin_items) {
    return TRUE;
  }

  gtk_tree_model_get(model, iter, WE_GUIED_POINTER, &object, -1);
  if (!object) {
    return FALSE;
  }

  if (((GeneralObject *) object)->owner_plugin) {
    return FALSE;
  }
  return TRUE;
}
