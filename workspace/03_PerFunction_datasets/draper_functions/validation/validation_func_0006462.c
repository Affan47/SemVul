evd_dbus_agent_close_proxy (GObject  *object,
                            guint     proxy_id,
                            GError  **error)
{
  g_return_val_if_fail (G_IS_OBJECT (object), FALSE);
  g_return_val_if_fail (proxy_id > 0, FALSE);

  if (evd_dbus_agent_get_proxy (object, proxy_id, error) != NULL)
    {
      ObjectData *data;

      data = evd_dbus_agent_get_object_data (object);

      g_hash_table_remove (data->proxies, &proxy_id);

      return TRUE;
    }
  else
    {
      return FALSE;
    }
}
