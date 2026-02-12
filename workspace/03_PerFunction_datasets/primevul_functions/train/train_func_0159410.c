receive_statvfs(BOOL isspool, int *inodeptr)
{
#ifdef HAVE_STATFS
struct STATVFS statbuf;
struct stat dummy;
uschar *path;
uschar *name;
uschar buffer[1024];


if (isspool)
  {
  path = spool_directory;
  name = US"spool";
  }


else
  {
  int sep = ':';
  const uschar *p = log_file_path;
  name = US"log";


  if (*p == 0) p = US":";
  while ((path = string_nextinlist(&p, &sep, buffer, sizeof(buffer))))
    if (Ustrcmp(path, "syslog") != 0)
      break;

  if (path == NULL)
    {
    *inodeptr = -1;
    return -1;
    }


  if (path[0] == 0)
    {
    sprintf(CS buffer, CS"%s/log", CS spool_directory);
    path = buffer;
    }
  else
    {
    uschar *cp;
    if ((cp = Ustrrchr(path, '/')) != NULL) *cp = 0;
    }
  }


memset(&statbuf, 0, sizeof(statbuf));

if (STATVFS(CS path, &statbuf) != 0)
  if (stat(CS path, &dummy) == -1 && errno == ENOENT)
    {
    *inodeptr = -1;
    return -1;
    }
  else
    {
    log_write(0, LOG_MAIN|LOG_PANIC, "cannot accept message: failed to stat "
      "%s directory %s: %s", name, path, strerror(errno));
    smtp_closedown(US"spool or log directory problem");
    exim_exit(EXIT_FAILURE, NULL);
    }

*inodeptr = (statbuf.F_FILES > 0)? statbuf.F_FAVAIL : -1;


return (int)(((double)statbuf.F_BAVAIL * (double)statbuf.F_FRSIZE)/1024.0);

#else


*inodeptr = -1;
return -1;
#endif
}
