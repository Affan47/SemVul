dconf_engine_dbus_call_async_func (GBusType                bus_type,
                                   const gchar            *bus_name,
                                   const gchar            *object_path,
                                   const gchar            *interface_name,
                                   const gchar            *method_name,
                                   GVariant               *parameters,
                                   DConfEngineCallHandle  *handle,
                                   GError                **error)
{
  ConnectionState *state;
  GDBusMessage *message;
  DConfGDBusCall *call;
  gboolean success;

  state = dconf_gdbus_get_connection_state (bus_type, error);

  if (state == NULL)
    {
      g_variant_unref (g_variant_ref_sink (parameters));
      return FALSE;
    }

  message = g_dbus_message_new_method_call (bus_name, object_path, interface_name, method_name);
  g_dbus_message_set_body (message, parameters);

  g_mutex_lock (&dconf_gdbus_lock);
  {
    volatile guint *serial_ptr;
    guint my_serial;


    if (g_queue_is_empty (&state->queue))
      serial_ptr = &state->waiting_for_serial;
    else
      serial_ptr = &my_serial;

    success = g_dbus_connection_send_message (connection_state_get_connection (state), message,
                                              G_DBUS_SEND_MESSAGE_FLAGS_NONE, serial_ptr, error);

    if (success)
      {
        call = g_slice_new (DConfGDBusCall);

        call->handle = handle;
        call->serial = *serial_ptr;

        g_queue_push_tail (&state->queue, call);
      }
  }
  g_mutex_unlock (&dconf_gdbus_lock);

  g_object_unref (message);

  return success;
}
