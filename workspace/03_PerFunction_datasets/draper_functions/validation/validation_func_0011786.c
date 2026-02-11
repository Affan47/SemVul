find_container_partition (UDisksPartitionTable     *table,
                          UDisksObject             *object,
                          guint64                   start,
                          guint64                   end)
{
  UDisksPartition *ret = NULL;
  UDisksDaemon *daemon = NULL;
  GDBusObjectManager *object_manager = NULL;
  const gchar *table_object_path;
  GList *objects = NULL, *l;

  daemon = udisks_linux_block_object_get_daemon (UDISKS_LINUX_BLOCK_OBJECT (object));
  object_manager = G_DBUS_OBJECT_MANAGER (udisks_daemon_get_object_manager (daemon));

  table_object_path = g_dbus_object_get_object_path (G_DBUS_OBJECT (object));

  objects = g_dbus_object_manager_get_objects (object_manager);
  for (l = objects; l != NULL; l = l->next)
    {
      UDisksObject *i_object = UDISKS_OBJECT (l->data);
      UDisksPartition *i_partition = NULL;

      i_partition = udisks_object_get_partition (i_object);

      if (i_partition == NULL)
        goto cont;

      if (g_strcmp0 (udisks_partition_get_table (i_partition), table_object_path) != 0)
        goto cont;

      if (udisks_partition_get_is_container (i_partition)
          && ranges_overlap (start, end - start,
                             udisks_partition_get_offset (i_partition),
                             udisks_partition_get_size (i_partition)))
        {
          ret = i_partition;
          goto out;
        }

    cont:
      g_clear_object (&i_partition);
    }

 out:
  g_list_foreach (objects, (GFunc) g_object_unref, NULL);
  g_list_free (objects);
  return ret;
}
