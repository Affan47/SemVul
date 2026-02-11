online_notify (gboolean online, gpointer user_data)
{
  SwServiceSmugmug *self = (SwServiceSmugmug *) user_data;
  SwService *service = SW_SERVICE (self);
  SwServiceSmugmugPrivate *priv = self->priv;

  if (online) {
    sw_keyfob_oauth ((OAuthProxy *) priv->auth_proxy, got_tokens_cb, self);
  } else {
    priv->authorized = FALSE;
    sw_service_emit_capabilities_changed (service, get_dynamic_caps (service));
  }
}
