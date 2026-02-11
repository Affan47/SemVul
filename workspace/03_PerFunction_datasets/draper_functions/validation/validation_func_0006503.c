append_reference (DBusMessageIter * iter, const char * name, const char * path)
{
  DBusMessageIter iter_struct;

  if (!dbus_message_iter_open_container (iter, DBUS_TYPE_STRUCT, NULL,
                                    &iter_struct))
    return FALSE;
  dbus_message_iter_append_basic (&iter_struct, DBUS_TYPE_STRING, &name);
  dbus_message_iter_append_basic (&iter_struct, DBUS_TYPE_OBJECT_PATH, &path);
  dbus_message_iter_close_container (iter, &iter_struct);
  return TRUE;
}
