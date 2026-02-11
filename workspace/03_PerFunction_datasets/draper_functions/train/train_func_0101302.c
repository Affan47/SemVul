get_row_value (GgdDoctypeSelector  *self,
               guint                language_id,
               guint                column,
               void                *result)
{
  GtkTreeIter iter;
  gboolean    found = FALSE;

  if (get_row_iter (self, language_id, &iter)) {
    gtk_tree_model_get (GTK_TREE_MODEL (self->priv->store), &iter,
                        column, result,
                        -1);
    found = TRUE;
  }

  return found;
}
