zlog_set_file (struct zlog *zl, const char *filename, int log_level)
{
  FILE *fp;
  mode_t oldumask;


  zlog_reset_file (zl);


  if (zl == NULL)
    zl = zlog_default;


  oldumask = umask (0777 & ~LOGFILE_MASK);
  fp = fopen (filename, "a");
  umask(oldumask);
  if (fp == NULL)
    return 0;


  zl->filename = strdup (filename);
  zl->maxlvl[ZLOG_DEST_FILE] = log_level;
  zl->fp = fp;
  logfile_fd = fileno(fp);

  return 1;
}
