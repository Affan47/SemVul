exo_icon_chooser_model_iter_n_children (GtkTreeModel *tree_model,
                                        GtkTreeIter  *iter)
{
  ExoIconChooserModel *model = EXO_ICON_CHOOSER_MODEL (tree_model);

  _exo_return_val_if_fail (EXO_IS_ICON_CHOOSER_MODEL (tree_model), 0);

  return (iter == NULL) ? g_list_length (model->items) : 0;
}
