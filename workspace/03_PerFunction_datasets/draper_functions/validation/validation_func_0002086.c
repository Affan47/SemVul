_cups_notifier_on_signal_job_state (
    CupsNotifier *object,
    const gchar *arg_text,
    const gchar *arg_printer_uri,
    const gchar *arg_printer_name,
    guint arg_printer_state,
    const gchar *arg_printer_state_reasons,
    gboolean arg_printer_is_accepting_jobs,
    guint arg_job_id,
    guint arg_job_state,
    const gchar *arg_job_state_reasons,
    const gchar *arg_job_name,
    guint arg_job_impressions_completed)
{
  CupsNotifierSkeleton *skeleton = CUPS_NOTIFIER_SKELETON (object);

  GList      *connections, *l;
  GVariant   *signal_variant;
  connections = g_dbus_interface_skeleton_get_connections (G_DBUS_INTERFACE_SKELETON (skeleton));

  signal_variant = g_variant_ref_sink (g_variant_new ("(sssusbuussu)",
                   arg_text,
                   arg_printer_uri,
                   arg_printer_name,
                   arg_printer_state,
                   arg_printer_state_reasons,
                   arg_printer_is_accepting_jobs,
                   arg_job_id,
                   arg_job_state,
                   arg_job_state_reasons,
                   arg_job_name,
                   arg_job_impressions_completed));
  for (l = connections; l != NULL; l = l->next)
    {
      GDBusConnection *connection = l->data;
      g_dbus_connection_emit_signal (connection,
        NULL, g_dbus_interface_skeleton_get_object_path (G_DBUS_INTERFACE_SKELETON (skeleton)), "org.cups.cupsd.Notifier", "JobState",
        signal_variant, NULL);
    }
  g_variant_unref (signal_variant);
  g_list_free_full (connections, g_object_unref);
}
