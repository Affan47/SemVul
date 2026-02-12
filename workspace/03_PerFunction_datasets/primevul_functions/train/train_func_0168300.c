write_xattr_metadata (const char *name, const char *value, FILE *fp)
{
  int retval = -1;

  if (name && value && fp)
    {
      retval = fsetxattr (fileno (fp), name, value, strlen (value), 0);

      retval = (retval < 0) ? retval : 0;
      if (retval)
        DEBUGP (("Failed to set xattr %s.\n", quote(name)));
    }

  return retval;
}
