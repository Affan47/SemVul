check_entry_text (GladeNamedIconChooserDialog * dialog,
                  gchar ** name_ret,
                  gboolean * is_wellformed_ret, gboolean * is_empty_ret)
{
  if (strlen (gtk_entry_get_text (GTK_ENTRY (dialog->priv->entry))) == 0)
    {
      *name_ret = NULL;
      *is_wellformed_ret = TRUE;
      *is_empty_ret = TRUE;

      return;
    }

  *is_empty_ret = FALSE;

  *is_wellformed_ret =
      is_well_formed (gtk_entry_get_text (GTK_ENTRY (dialog->priv->entry)));

  if (*is_wellformed_ret)
    *name_ret = g_strdup (gtk_entry_get_text (GTK_ENTRY (dialog->priv->entry)));
  else
    *name_ret = NULL;
}
