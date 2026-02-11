dbus_bus_register (DBusConnection *connection,
                   DBusError      *error)
{
  DBusMessage *message, *reply;
  char *name;
  BusData *bd;
  dbus_bool_t retval;

  _dbus_return_val_if_fail (connection != NULL, FALSE);
  _dbus_return_val_if_error_is_set (error, FALSE);

  retval = FALSE;
  message = NULL;
  reply = NULL;

  _DBUS_LOCK (bus_datas);

  bd = ensure_bus_data (connection);
  if (bd == NULL)
    {
      _DBUS_SET_OOM (error);
      goto out;
    }

  if (bd->unique_name != NULL)
    {
      _dbus_verbose ("Ignoring attempt to register the same DBusConnection %s with the message bus a second time.\n",
                     bd->unique_name);

      retval = TRUE;
      goto out;
    }

  message = dbus_message_new_method_call (DBUS_SERVICE_DBUS,
                                          DBUS_PATH_DBUS,
                                          DBUS_INTERFACE_DBUS,
                                          "Hello");

  if (!message)
    {
      _DBUS_SET_OOM (error);
      goto out;
    }

  reply = dbus_connection_send_with_reply_and_block (connection, message, -1, error);

  if (reply == NULL)
    goto out;
  else if (dbus_set_error_from_message (error, reply))
    goto out;
  else if (!dbus_message_get_args (reply, error,
                                   DBUS_TYPE_STRING, &name,
                                   DBUS_TYPE_INVALID))
    goto out;

  bd->unique_name = _dbus_strdup (name);
  if (bd->unique_name == NULL)
    {
      _DBUS_SET_OOM (error);
      goto out;
    }

  retval = TRUE;

 out:
  _DBUS_UNLOCK (bus_datas);

  if (message)
    dbus_message_unref (message);

  if (reply)
    dbus_message_unref (reply);

  if (!retval)
    _DBUS_ASSERT_ERROR_IS_SET (error);

  return retval;
}
