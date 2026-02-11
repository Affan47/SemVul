shared_connections_shutdown (void *data)
{
  int n_entries;

  _DBUS_LOCK (shared_connections);


  while ((n_entries = _dbus_hash_table_get_n_entries (shared_connections)) > 0)
    {
      DBusConnection *connection;
      DBusHashIter iter;

      _dbus_hash_iter_init (shared_connections, &iter);
      _dbus_hash_iter_next (&iter);

      connection = _dbus_hash_iter_get_value (&iter);

      _DBUS_UNLOCK (shared_connections);
      close_connection_on_shutdown (connection);
      _DBUS_LOCK (shared_connections);


      _dbus_assert (_dbus_hash_table_get_n_entries (shared_connections) < n_entries);
    }

  _dbus_assert (_dbus_hash_table_get_n_entries (shared_connections) == 0);

  _dbus_hash_table_unref (shared_connections);
  shared_connections = NULL;

  if (shared_connections_no_guid != NULL)
    {
      DBusConnection *connection;
      connection = _dbus_list_pop_first (&shared_connections_no_guid);
      while (connection != NULL)
        {
          _DBUS_UNLOCK (shared_connections);
          close_connection_on_shutdown (connection);
          _DBUS_LOCK (shared_connections);
          connection = _dbus_list_pop_first (&shared_connections_no_guid);
        }
    }

  shared_connections_no_guid = NULL;

  _DBUS_UNLOCK (shared_connections);
}
