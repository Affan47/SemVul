guestfs___first_egrep_of_file (guestfs_h *g, const char *filename,
                               const char *eregex, int iflag, char **ret)
{
  char **lines;
  int64_t size;
  size_t i;
  struct guestfs_grep_opts_argv optargs;


  size = guestfs_filesize (g, filename);
  if (size == -1)

    return -1;
  if (size > MAX_SMALL_FILE_SIZE) {
    error (g, _("size of %s is unreasonably large (%" PRIi64 " bytes)"),
           filename, size);
    return -1;
  }

  optargs.bitmask = GUESTFS_GREP_OPTS_EXTENDED_BITMASK;
  optargs.extended = 1;
  if (iflag) {
    optargs.bitmask |= GUESTFS_GREP_OPTS_INSENSITIVE_BITMASK;
    optargs.insensitive = 1;
  }
  lines = guestfs_grep_opts_argv (g, eregex, filename, &optargs);
  if (lines == NULL)
    return -1;
  if (lines[0] == NULL) {
    guestfs___free_string_list (lines);
    return 0;
  }

  *ret = lines[0];


  for (i = 1; lines[i] != NULL; ++i)
    free (lines[i]);
  free (lines);

  return 1;
}
