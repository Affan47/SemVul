sfe(name, argv)
char *name;
char *argv[];
{
  int fildes[2];

  if (socketpair(PF_UNIX, SOCK_STREAM, 0, fildes) == -1) {
    fildes[0] = -1;
  } else {

#if defined(__sgi)
    switch (fork()) {
#else
    switch (vfork()) {
#endif
    case -1:
      fildes[0] = -1;
      (void)close(fildes[1]);
      break;
    case 0:

      (void)close(fildes[0]);


      (void)close(0);
      if (dup(fildes[1]) != 0) {

	_exit(1);
      }


      (void)close(1);
      if (dup(fildes[1]) != 1) {

	_exit(1);
      }
      (void)close(fildes[1]);


      (void)execvp(name, argv);


      handler(1);
      _exit(1);
      break;
    default:
      (void)close(fildes[1]);
      break;
    }
  }
  return fildes[0];
}
