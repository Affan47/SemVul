_dbus_get_autolaunch_address (const char *scope,
                              DBusString *address,
                              DBusError  *error)
{
#ifdef DBUS_ENABLE_X11_AUTOLAUNCH
  static const char arg_dbus_launch[] = "dbus-launch";
  static const char arg_autolaunch[] = "--autolaunch";
  static const char arg_binary_syntax[] = "--binary-syntax";
  static const char arg_close_stderr[] = "--close-stderr";


  const char *display;
  const char *progpath;
  const char *argv[6];
  int i;
  DBusString uuid;
  dbus_bool_t retval;

  if (_dbus_check_setuid ())
    {
      dbus_set_error_const (error, DBUS_ERROR_NOT_SUPPORTED,
                            "Unable to autolaunch when setuid");
      return FALSE;
    }

  _DBUS_ASSERT_ERROR_IS_CLEAR (error);
  retval = FALSE;


  display = _dbus_getenv ("DISPLAY");

  if (display == NULL || display[0] == '\0')
    {
      dbus_set_error_const (error, DBUS_ERROR_NOT_SUPPORTED,
          "Unable to autolaunch a dbus-daemon without a $DISPLAY for X11");
      return FALSE;
    }

  if (!_dbus_string_init (&uuid))
    {
      _DBUS_SET_OOM (error);
      return FALSE;
    }

  if (!_dbus_get_local_machine_uuid_encoded (&uuid, error))
    {
      goto out;
    }

#ifdef DBUS_ENABLE_EMBEDDED_TESTS
  progpath = _dbus_getenv ("DBUS_TEST_DBUS_LAUNCH");

  if (progpath == NULL)
#endif
    progpath = DBUS_BINDIR "/dbus-launch";


  i = 0;
  argv[i] = arg_dbus_launch;
  ++i;
  argv[i] = arg_autolaunch;
  ++i;
  argv[i] = _dbus_string_get_data (&uuid);
  ++i;
  argv[i] = arg_binary_syntax;
  ++i;
  argv[i] = arg_close_stderr;
  ++i;
  argv[i] = NULL;
  ++i;

  _dbus_assert (i == _DBUS_N_ELEMENTS (argv));

  retval = _read_subprocess_line_argv (progpath,
                                       TRUE,
                                       argv, address, error);

 out:
  _dbus_string_free (&uuid);
  return retval;
#else
  dbus_set_error_const (error, DBUS_ERROR_NOT_SUPPORTED,
      "Using X11 for dbus-daemon autolaunch was disabled at compile time, "
      "set your DBUS_SESSION_BUS_ADDRESS instead");
  return FALSE;
#endif
}
