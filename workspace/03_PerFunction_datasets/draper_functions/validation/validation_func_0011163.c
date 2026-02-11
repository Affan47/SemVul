update_blocks (GduDeviceTreeModel *model)
{
  GDBusObjectManager *object_manager;
  GList *objects;
  GList *blocks;
  GList *added_blocks;
  GList *removed_blocks;
  GList *l;

  object_manager = udisks_client_get_object_manager (model->client);
  objects = g_dbus_object_manager_get_objects (object_manager);

  blocks = NULL;
  for (l = objects; l != NULL; l = l->next)
    {
      UDisksObject *object = UDISKS_OBJECT (l->data);
      UDisksBlock *block;

      block = udisks_object_peek_block (object);
      if (block == NULL)
        continue;

      if (should_include_block (object))
        blocks = g_list_prepend (blocks, g_object_ref (object));
    }

  blocks = g_list_sort (blocks, (GCompareFunc) _g_dbus_object_compare);
  model->current_blocks = g_list_sort (model->current_blocks, (GCompareFunc) _g_dbus_object_compare);
  diff_sorted_lists (model->current_blocks,
                     blocks,
                     (GCompareFunc) _g_dbus_object_compare,
                     &added_blocks,
                     &removed_blocks);

  for (l = removed_blocks; l != NULL; l = l->next)
    {
      UDisksObject *object = UDISKS_OBJECT (l->data);

      g_assert (g_list_find (model->current_blocks, object) != NULL);

      model->current_blocks = g_list_remove (model->current_blocks, object);
      remove_block (model, object);
      g_object_unref (object);
    }
  for (l = added_blocks; l != NULL; l = l->next)
    {
      UDisksObject *object = UDISKS_OBJECT (l->data);
      model->current_blocks = g_list_prepend (model->current_blocks, g_object_ref (object));
      add_block (model, object, get_block_header_iter (model));
    }

  for (l = model->current_blocks; l != NULL; l = l->next)
    {
      UDisksObject *object = UDISKS_OBJECT (l->data);
      update_block (model, object, FALSE);
    }

  if (g_list_length (model->current_blocks) == 0)
    nuke_block_header (model);

  g_list_free (added_blocks);
  g_list_free (removed_blocks);
  g_list_foreach (blocks, (GFunc) g_object_unref, NULL);
  g_list_free (blocks);

  g_list_foreach (objects, (GFunc) g_object_unref, NULL);
  g_list_free (objects);
}
