worklist_next_to_last_impr_or_unit_iterate(GtkTreeModel *model,
                                                       GtkTreePath *path,
                                                       GtkTreeIter *iter,
                                                       gpointer data)
{
  struct universal target = cid_decode(GPOINTER_TO_INT(data));
  struct city *pcity = city_model_get(model, iter);

  if (NULL != pcity) {
    city_queue_insert(pcity, worklist_length(&pcity->worklist), target);
  }
}
