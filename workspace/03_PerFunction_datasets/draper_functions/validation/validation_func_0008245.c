console_kit_session_call_get_unix_user_sync (
    ConsoleKitSession *proxy,
    guint *out_uid,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "GetUnixUser",
    g_variant_new ("()"),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(u)",
                 out_uid);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}
