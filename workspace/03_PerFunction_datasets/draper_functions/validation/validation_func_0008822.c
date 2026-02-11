photos_fetch_collection_state_job_job_collector (GList *collections_for_item, gpointer user_data)
{
  PhotosFetchCollectionStateJobData *data = user_data;
  PhotosFetchCollectionStateJob *self = data->job;
  PhotosFetchCollectionStateJobPrivate *priv = self->priv;
  const gchar *urn = data->urn;

  g_hash_table_insert (priv->collections_for_items,
                       g_strdup (urn),
                       g_list_copy_deep (collections_for_item, (GCopyFunc) g_strdup, NULL));

  priv->running_jobs--;
  if (priv->running_jobs == 0)
    photos_fetch_collection_state_job_emit_callback (self);

  photos_fetch_collection_state_job_data_free (data);
}
