tp_channel_get_handle (TpChannel *self,
                       TpHandleType *handle_type)
{
  g_return_val_if_fail (TP_IS_CHANNEL (self), 0);

  if (handle_type != NULL)
    {
      *handle_type = self->priv->handle_type;
    }

  return self->priv->handle;
}
