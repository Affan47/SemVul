_dbus_keyring_unlock (DBusKeyring *keyring)
{
  DBusError error = DBUS_ERROR_INIT;

  if (!_dbus_delete_file (&keyring->filename_lock, &error))
    {
      _dbus_warn ("Failed to delete lock file: %s\n",
                  error.message);
      dbus_error_free (&error);
    }
}
