empathy_account_selector_dialog_dup_selected (
    EmpathyAccountSelectorDialog *self)
{
  GtkTreeSelection *selection;
  GtkTreeIter iter;
  GtkTreeModel *model;
  TpAccount *account;

  selection = gtk_tree_view_get_selection (
      GTK_TREE_VIEW (self->priv->treeview));

  if (!gtk_tree_selection_get_selected (selection, &model, &iter))
    return NULL;

  gtk_tree_model_get (model, &iter, COL_ACCOUNT, &account, -1);

  return account;
}
