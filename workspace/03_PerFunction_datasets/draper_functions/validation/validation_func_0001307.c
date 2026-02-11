online_notify (gboolean online, gpointer user_data)
{
  SwServiceFacebook *service = (SwServiceFacebook *) user_data;
  SwServiceFacebookPrivate *priv = service->priv;
  priv->online = online;

  if (online) {
    sw_keyfob_oauth2 ((OAuth2Proxy *)priv->proxy, got_tokens_cb, service);
  } else {
    sw_service_emit_capabilities_changed ((SwService *)service,
                                          get_dynamic_caps ((SwService*)service));
    g_free (priv->uid);
    priv->uid = NULL;
  }
}
