file_read_async_cb (GObject *source,
    GAsyncResult *res,
    gpointer user_data)
{
  TpFileTransferChannel *self = user_data;
  GFileInputStream *in_stream;
  GError *error = NULL;
  GFile *file = G_FILE (source);

  in_stream = g_file_read_finish (file, res, &error);

  if (error != NULL)
    {
      operation_failed (self, error);
      return;
    }

  self->priv->in_stream = G_INPUT_STREAM (in_stream);

  g_clear_object (&self->priv->file);
  self->priv->file = g_object_ref (file);

  if (!set_address_and_access_control (self))
    return;


  tp_cli_channel_type_file_transfer_call_provide_file (TP_CHANNEL (self), -1,
      self->priv->socket_type,
      self->priv->access_control,
      self->priv->access_control_param,
      accept_or_provide_file_cb,
      NULL, NULL, G_OBJECT (self));
}
