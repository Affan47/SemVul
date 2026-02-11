classbrowser_classid_to_iter(GtkTreeModel *model, guint classid, GtkTreeIter *iter)
{
  guint id;
  gboolean found;

  if (gtk_tree_model_get_iter_first(model, iter)) {
    found = TRUE;
    while (found) {
      gtk_tree_model_get(model,iter, ID_COLUMN, &id,-1);
      if (id == classid) {
        return TRUE;
      }
      found = gtk_tree_model_iter_next(model, iter);
    }
  }
  return FALSE;
}
