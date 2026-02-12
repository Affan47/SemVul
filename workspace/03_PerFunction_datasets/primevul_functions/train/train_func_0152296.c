_dbus_printf_string_upper_bound (const char *format,
                                 va_list     args)
{
  char static_buf[1024];
  int bufsize = sizeof (static_buf);
  int len;
  va_list args_copy;

  DBUS_VA_COPY (args_copy, args);
  len = vsnprintf (static_buf, bufsize, format, args_copy);
  va_end (args_copy);


  if (len == bufsize)
    {


      DBUS_VA_COPY (args_copy, args);

      if (vsnprintf (static_buf, 1, format, args_copy) == 1)
        len = -1;

      va_end (args_copy);
    }


  while (len < 0)
    {
      char *buf;

      bufsize *= 2;

      buf = dbus_malloc (bufsize);

      if (buf == NULL)
        return -1;

      DBUS_VA_COPY (args_copy, args);
      len = vsnprintf (buf, bufsize, format, args_copy);
      va_end (args_copy);

      dbus_free (buf);


      if (len == bufsize)
        len = -1;
    }

  return len;
}
