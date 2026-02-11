tp_file_transfer_channel_prepare_core_cb (TpProxy *proxy,
    GHashTable *properties,
    const GError *error,
    gpointer user_data,
    GObject *weak_object)
{
  TpFileTransferChannel *self = (TpFileTransferChannel *) proxy;
  GSimpleAsyncResult *result = user_data;
  gboolean valid;
  const gchar *uri;

  if (error != NULL)
    {
      g_simple_async_result_set_from_error (result, error);
      goto out;
    }

  self->priv->state = tp_asv_get_uint32 (properties, "State", &valid);
  if (!valid)
    {
      DEBUG ("Channel %s doesn't have FileTransfer.State property",
          tp_proxy_get_object_path (self));
    }

  self->priv->transferred_bytes = tp_asv_get_uint64 (properties,
      "TransferredBytes", &valid);
  if (!valid)
    {
      DEBUG ("Channel %s doesn't have FileTransfer.TransferredBytes property",
          tp_proxy_get_object_path (self));
    }

  self->priv->initial_offset = tp_asv_get_uint64 (properties, "InitialOffset",
      &valid);
  if (!valid)
    {
      DEBUG ("Channel %s doesn't have FileTransfer.InitialOffset property",
          tp_proxy_get_object_path (self));
    }


  uri = tp_asv_get_string (properties, "URI");
  if (self->priv->file == NULL && uri != NULL)
    self->priv->file = g_file_new_for_uri (uri);

out:
  g_simple_async_result_complete_in_idle (result);
}
