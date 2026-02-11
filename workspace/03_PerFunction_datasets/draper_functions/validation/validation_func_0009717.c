name_cell_func (GtkTreeViewColumn *column,
                GtkCellRenderer   *renderer,
                GtkTreeModel      *model,
                GtkTreeIter       *iter,
                gpointer           user_data)
{
  DialogData *data = user_data;
  UDisksBlock *block = NULL;
  UDisksObject *object = NULL;
  UDisksObjectInfo *info = NULL;
  gchar *markup = NULL;

  gtk_tree_model_get (model,
                      iter,
                      COLUMN_BLOCK, &block,
                      -1);

  if (block == NULL)
    goto out;

  object = (UDisksObject *) g_dbus_interface_dup_object (G_DBUS_INTERFACE (block));
  if (object == NULL)
    goto out;

  info = udisks_client_get_object_info (data->client, object);
  markup = g_strdup (udisks_object_info_get_description (info));

 out:

  g_object_set (renderer,
                "markup", markup,
                NULL);

  g_free (markup);
  g_clear_object (&object);
  g_clear_object (&block);
  g_clear_object (&info);
}
