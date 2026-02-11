dbus_watch_get_unix_fd (DBusWatch *watch)
{
  _dbus_return_val_if_fail (watch != NULL, -1);


#ifdef DBUS_UNIX
  return watch->fd;
#else
  return dbus_watch_get_socket( watch );
#endif
}
