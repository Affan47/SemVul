int ss_daemon_init() {
#ifdef OS_UNIX


   int i, fd, pid;

   if ((pid = fork()) < 0)
      return FAILURE;
   else if (pid != 0)
      _exit(EXIT_SUCCESS);


   for (i = 0; i < 3; i++) {
      close(i);
      fd = open("/dev/null", O_RDWR, 0);
      if (fd < 0)
         fd = open("/dev/null", O_WRONLY, 0);
      if (fd < 0) {
         eprintf("Can't open /dev/null");
         return FAILURE;
      }
      if (fd != i) {
         eprintf("Did not get file descriptor");
         return FAILURE;
      }
   }

   setsid();
   chdir("/");
   umask(0);

#endif

   return SUCCESS;
}
