pending_select_name_process (GladeNamedIconChooserDialog * dialog)
{
  ForEachFuncData *data;

  g_assert (dialog->priv->icons_store != NULL);
  g_assert (dialog->priv->selection != NULL);

  if (dialog->priv->pending_select_name)
    {

      data = g_slice_new0 (ForEachFuncData);

      data->name = dialog->priv->pending_select_name;
      data->do_select = TRUE;
      data->do_activate = FALSE;
      data->dialog = dialog;

      gtk_tree_model_foreach (dialog->priv->filter_model,
                              scan_for_name_func, data);

      g_free (dialog->priv->pending_select_name);
      dialog->priv->pending_select_name = NULL;

      g_slice_free (ForEachFuncData, data);

    }
  else
    {
      if (strlen (gtk_entry_get_text (GTK_ENTRY (dialog->priv->entry))) == 0)
        {
          select_first_row (dialog);
        }
    }

  centre_selected_row (dialog);
}
