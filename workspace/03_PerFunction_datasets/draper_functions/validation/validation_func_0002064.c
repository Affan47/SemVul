install_package_names_cb (GObject *source,
    GAsyncResult *result,
    gpointer user_data)
{
  InstallCtx *ctx = user_data;
  GError *error = NULL;
  GVariant *res;

  res = g_dbus_proxy_call_finish (G_DBUS_PROXY (source), result, &error);
  if (res == NULL)
    {
      install_ctx_failed (ctx, error);
      return;
    }

  install_ctx_complete (ctx);

  g_variant_unref (res);
}
