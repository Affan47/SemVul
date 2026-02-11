_tp_account_got_all_cb (TpProxy *proxy,
    GHashTable *properties,
    const GError *error,
    gpointer user_data,
    GObject *weak_object)
{
  TpAccount *self = TP_ACCOUNT (weak_object);

  DEBUG ("Got whole set of properties for %s",
      tp_proxy_get_object_path (self));

  if (error != NULL)
    {
      DEBUG ("Failed to get the initial set of account properties: %s",
          error->message);
      tp_proxy_invalidate ((TpProxy *) self, error);
      return;
    }

  _tp_account_update (self, properties);
}
