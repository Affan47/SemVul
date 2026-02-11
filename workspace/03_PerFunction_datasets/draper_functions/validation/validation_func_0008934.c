ipmiconsole_debug_setup (uint32_t debug_flags)
{
  assert (debug_flags == IPMICONSOLE_DEBUG_DEFAULT
	  || !(debug_flags & ~IPMICONSOLE_DEBUG_MASK));

  if (debug_flags == IPMICONSOLE_DEBUG_DEFAULT)
    console_debug_flags = 0;
  else
    console_debug_flags = debug_flags;

  if (console_debug_flags & IPMICONSOLE_DEBUG_FILE)
    {
      char filename[MAXPATHLEN];
      snprintf (filename,
                MAXPATHLEN,
                "%s/%s",
                IPMICONSOLE_DEBUG_DIRECTORY,
                IPMICONSOLE_DEBUG_FILENAME);

      if ((console_debug_fd = open (filename, O_CREAT | O_APPEND | O_WRONLY | O_EXCL, 0600)) < 0)
        {
          console_debug_flags &= ~IPMICONSOLE_DEBUG_FILE;
          IPMICONSOLE_DEBUG (("open: %s", strerror (errno)));
          console_debug_flags = 0;
          return (-1);
        }
    }

  return (0);
}
