_gtk_mount_operation_handler_call_show_processes_sync (
    _GtkMountOperationHandler *proxy,
    const gchar *arg_id,
    const gchar *arg_message,
    const gchar *arg_icon_name,
    GVariant *arg_application_pids,
    const gchar *const *arg_choices,
    guint *out_response,
    GVariant **out_response_details,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "ShowProcesses",
    g_variant_new ("(sss@ai^as)",
                   arg_id,
                   arg_message,
                   arg_icon_name,
                   arg_application_pids,
                   arg_choices),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(u@a{sv})",
                 out_response,
                 out_response_details);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}
