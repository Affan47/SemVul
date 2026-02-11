dconf_writer_real_change (DConfWriter    *writer,
                          DConfChangeset *changeset,
                          const gchar    *tag)
{
  g_return_if_fail (writer->priv->uncommited_values != NULL);

  dconf_changeset_change (writer->priv->uncommited_values, changeset);

  if (tag)
    {
      TaggedChange *change;

      change = g_slice_new (TaggedChange);
      change->changeset = dconf_changeset_ref (changeset);
      change->tag = g_strdup (tag);

      g_queue_push_tail (&writer->priv->uncommited_changes, change);
    }

  writer->priv->need_write = TRUE;
}
