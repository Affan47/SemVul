dbus_message_get_signature (DBusMessage *message)
{
  const DBusString *type_str;
  int type_pos;

  _dbus_return_val_if_fail (message != NULL, NULL);

  get_const_signature (&message->header, &type_str, &type_pos);

  return _dbus_string_get_const_data_len (type_str, type_pos, 0);
}
