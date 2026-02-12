handle_client_initial_response_anonymous_mech (DBusAuth         *auth,
                                               DBusString       *response)
{


  DBusString plaintext;

  if (!_dbus_string_init (&plaintext))
    return FALSE;

  if (!_dbus_string_append (&plaintext,
                            "libdbus " DBUS_VERSION_STRING))
    goto failed;

  if (!_dbus_string_hex_encode (&plaintext, 0,
				response,
				_dbus_string_get_length (response)))
    goto failed;

  _dbus_string_free (&plaintext);

  return TRUE;

 failed:
  _dbus_string_free (&plaintext);
  return FALSE;
}
