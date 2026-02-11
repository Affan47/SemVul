gtr_message_table_model_iter_nth_child (GtkTreeModel * tree_model,
                                        GtkTreeIter * iter,
                                        GtkTreeIter * parent, gint n)
{
  GtrMessageTableModel *model = GTR_MESSAGE_TABLE_MODEL (tree_model);

  if (parent)
    return FALSE;

  if (n < 0 || n >= gtr_message_container_get_count (model->container))
    return FALSE;

  iter->stamp = GTR_MESSAGE_TABLE_MODEL (tree_model)->stamp;
  iter->user_data = gtr_message_container_get_message (model->container, n);
  iter->user_data2 = GINT_TO_POINTER (n);

  return TRUE;
}
