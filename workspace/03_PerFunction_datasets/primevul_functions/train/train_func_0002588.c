_dbus_printf_string_upper_bound (const char *format,
                                 va_list     args)
{
  char static_buf[1024];
  int bufsize = sizeof (static_buf);
  int len;

  len = vsnprintf (static_buf, bufsize, format, args);


  if (len == bufsize)
    {


      if (vsnprintf (static_buf, 1, format, args) == 1)
        len = -1;
    }


  while (len < 0)
    {
      char *buf;

      bufsize *= 2;

      buf = dbus_malloc (bufsize);

      if (buf == NULL)
        return -1;

      len = vsnprintf (buf, bufsize, format, args);
      dbus_free (buf);


      if (len == bufsize)
        len = -1;
    }

  return len;
}
