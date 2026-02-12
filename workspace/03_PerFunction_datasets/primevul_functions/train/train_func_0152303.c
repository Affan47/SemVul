_dbus_get_tmpdir(void)
{

  static const char* tmpdir = NULL;

  if (!_DBUS_LOCK (sysdeps))
    return NULL;

  if (tmpdir == NULL)
    {


      if (tmpdir == NULL)
        tmpdir = getenv("TMPDIR");


      if (tmpdir == NULL)
        tmpdir = getenv("TMP");
      if (tmpdir == NULL)
        tmpdir = getenv("TEMP");


      if (tmpdir == NULL)
        tmpdir = "/tmp";
    }

  _DBUS_UNLOCK (sysdeps);

  _dbus_assert(tmpdir != NULL);

  return tmpdir;
}
