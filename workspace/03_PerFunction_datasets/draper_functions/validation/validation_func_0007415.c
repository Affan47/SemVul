vsprint_msg (const char *origmsg, const char *fmt, int arglen, ...)
{


  static bfd_size_type alloc_size = 0;
  static char *message = NULL;
  bfd_size_type orig_len, len = 0;
  bfd_boolean is_append;

  VA_OPEN (ap, arglen);
  VA_FIXEDARG (ap, const char *, origmsg);

  is_append = (origmsg == message);

  orig_len = strlen (origmsg);
  len = orig_len + strlen (fmt) + arglen + 20;
  if (len > alloc_size)
    {
      message = (char *) bfd_realloc_or_free (message, len);
      alloc_size = len;
    }
  if (message != NULL)
    {
      if (!is_append)
	memcpy (message, origmsg, orig_len);
      vsprintf (message + orig_len, fmt, ap);
    }
  VA_CLOSE (ap);
  return message;
}
