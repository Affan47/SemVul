_dbus_timeout_unref (DBusTimeout *timeout)
{
  _dbus_assert (timeout != NULL);
  _dbus_assert (timeout->refcount > 0);

  timeout->refcount -= 1;
  if (timeout->refcount == 0)
    {
      dbus_timeout_set_data (timeout, NULL, NULL);

      if (timeout->free_handler_data_function)
	(* timeout->free_handler_data_function) (timeout->handler_data);

      dbus_free (timeout);
    }
}
