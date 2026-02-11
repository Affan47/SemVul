make_exclude_from_file (char *const *excludes)
{
  size_t i;
  int fd;
  char template[] = "/tmp/excludesXXXXXX";
  char *ret;

  fd = mkstemp (template);
  if (fd == -1) {
    reply_with_perror ("mkstemp");
    return NULL;
  }

  for (i = 0; excludes[i] != NULL; ++i) {
    if (strchr (excludes[i], '\n')) {
      reply_with_error ("tar-out: excludes file patterns cannot contain \\n character");
      goto error;
    }

    if (xwrite (fd, excludes[i], strlen (excludes[i])) == -1 ||
        xwrite (fd, "\n", 1) == -1) {
      reply_with_perror ("write");
      goto error;
    }

    if (verbose)
      fprintf (stderr, "tar-out: adding excludes pattern '%s'\n", excludes[i]);
  }

  if (close (fd) == -1) {
    reply_with_perror ("close");
    fd = -1;
    goto error;
  }
  fd = -1;

  ret = strdup (template);
  if (ret == NULL) {
    reply_with_perror ("strdup");
    goto error;
  }

  return ret;

 error:
  if (fd >= 0)
    close (fd);
  unlink (template);
  return NULL;
}
