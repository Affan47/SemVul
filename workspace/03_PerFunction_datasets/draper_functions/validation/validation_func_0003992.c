evd_connection_unlock_close (EvdConnection *self)
{
  g_return_if_fail (EVD_IS_CONNECTION (self));

  self->priv->close_locked = FALSE;

  if (self->priv->delayed_close)
    evd_connection_close_in_idle (self);
}
