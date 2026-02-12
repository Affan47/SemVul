static void cleanChildren(pid_t pid, OFBool synch)


{
#ifdef HAVE_WAITPID
  int stat_loc;
#elif HAVE_WAIT3
  struct rusage rusage;
#if defined(__NeXT__)

  union wait status;
#else
  int        status;
#endif
#endif

#if defined(HAVE_WAITPID) || defined(HAVE_WAIT3)
  int child = 1;
  int options = synch ? 0 : WNOHANG;
  while (child > 0)
  {
#ifdef HAVE_WAITPID
    child = OFstatic_cast(int, waitpid(pid, &stat_loc, options));
#elif defined(HAVE_WAIT3)
    child = wait3(&status, options, &rusage);
#endif
    if (child < 0)
    {
      if (errno != ECHILD)
      {
        char buf[256];
        OFLOG_WARN(storescpLogger, "wait for child failed: " << OFStandard::strerror(errno, buf, sizeof(buf)));
      }
    }

    if (synch) child = -1;
  }
#endif
}
