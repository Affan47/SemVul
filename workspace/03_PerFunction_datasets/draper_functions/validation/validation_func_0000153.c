_fill_dialog_with_data (FrogrAddToGroupDialog *self)
{
  FrogrAddToGroupDialogPrivate *priv = NULL;
  GtkTreeIter iter;
  gint n_groups;
  gint n_pictures;

  priv = FROGR_ADD_TO_GROUP_DIALOG_GET_PRIVATE (self);
  n_groups = g_slist_length (priv->groups);
  n_pictures = g_slist_length (priv->pictures);


  if (n_groups == 0 || n_pictures == 0)
    return;


  gtk_tree_model_get_iter_first (priv->treemodel, &iter);
  do
    {
      FrogrGroup *group = NULL;
      GSList *p_item = NULL;
      gboolean do_check = TRUE;

      gtk_tree_model_get (GTK_TREE_MODEL (priv->treemodel), &iter,
                          GROUP_COL, &group, -1);

      for (p_item = priv->pictures; p_item; p_item = g_slist_next (p_item))
        {
          FrogrPicture *picture = NULL;

          picture = FROGR_PICTURE (p_item->data);
          if (!frogr_picture_in_group (picture, group))
            {
              do_check = FALSE;
              break;
            }
        }
      g_object_unref (group);

      gtk_list_store_set (GTK_LIST_STORE (priv->treemodel), &iter,
                          CHECKBOX_COL, do_check, -1);
    }
  while (gtk_tree_model_iter_next (priv->treemodel, &iter));
}
