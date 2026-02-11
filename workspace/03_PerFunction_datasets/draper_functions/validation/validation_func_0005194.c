server_handle_cancel_check_authorization (Server                 *server,
                                          GVariant               *parameters,
                                          PolkitSubject          *caller,
                                          GDBusMethodInvocation  *invocation)
{
  CheckAuthData *data;
  const gchar *cancellation_id;
  gchar *full_cancellation_id;

  g_variant_get (parameters, "(&s)", &cancellation_id);

  full_cancellation_id = g_strdup_printf ("%s-%s",
                                          g_dbus_method_invocation_get_sender (invocation),
                                          cancellation_id);

  data = g_hash_table_lookup (server->cancellation_id_to_check_auth_data, full_cancellation_id);
  if (data == NULL)
    {
      g_dbus_method_invocation_return_error (invocation,
                                             POLKIT_ERROR,
                                             POLKIT_ERROR_FAILED,
                                             "No such cancellation_id `%s' for name %s",
                                             cancellation_id,
                                             g_dbus_method_invocation_get_sender (invocation));
      goto out;
    }

  g_cancellable_cancel (data->cancellable);

  g_dbus_method_invocation_return_value (invocation, g_variant_new ("()"));

 out:
  g_free (full_cancellation_id);
}
