_check_access_token_cb (RestProxyCall *call,
                        const GError  *error,
                        GObject       *weak_object,
                        gpointer       user_data)
{
  RestXmlNode *root;
  GError *err = NULL;
  SwServicePhotobucket *self = SW_SERVICE_PHOTOBUCKET (weak_object);
  SwService *service = SW_SERVICE (self);
  SwServicePhotobucketPrivate *priv = self->priv;

  g_free (priv->uid);
  priv->uid = NULL;

  root = node_from_call (call, &err);

  if (err != NULL) {
    SW_DEBUG (PHOTOBUCKET, "Invalid access token: %s", err->message);
    g_error_free (err);
    return;
  }

  if (root != NULL) {
    RestXmlNode *api = rest_xml_node_find(root, "api");
    RestXmlNode *username = rest_xml_node_find(root, "username");

    if (api != NULL) {
      SW_DEBUG (PHOTOBUCKET, "silo subdomain: %s", api->content);
      rest_proxy_bind (priv->silo_proxy, api->content);
    } else {
      g_warning ("no silo subdomain");
    }

    if (username != NULL)
      priv->uid = g_strdup (username->content);
    else
      g_warning ("no username");
  }

  sw_service_emit_capabilities_changed (service, get_dynamic_caps (service));
}
