handle_server_data_anonymous_mech (DBusAuth         *auth,
                                   const DBusString *data)
{
  if (_dbus_string_get_length (data) > 0)
    {


      if (!_dbus_string_validate_utf8 (data, 0, _dbus_string_get_length (data)))
        {
          _dbus_verbose ("%s: Received invalid UTF-8 trace data from ANONYMOUS client\n",
                         DBUS_AUTH_NAME (auth));
          return send_rejected (auth);
        }

      _dbus_verbose ("%s: ANONYMOUS client sent trace string: '%s'\n",
                     DBUS_AUTH_NAME (auth),
                     _dbus_string_get_const_data (data));
    }


  _dbus_credentials_clear (auth->desired_identity);


  if (!_dbus_credentials_add_credential (auth->authorized_identity,
                                         DBUS_CREDENTIAL_UNIX_PROCESS_ID,
                                         auth->credentials))
    return FALSE;


  if (!send_ok (auth))
    return FALSE;

  _dbus_verbose ("%s: authenticated client as anonymous\n",
                 DBUS_AUTH_NAME (auth));

  return TRUE;
}
