kwsysProcessSetupOutputPipeNative(int* p, int des[2])
{

  kwsysProcessCleanupDescriptor(p);


  if ((fcntl(des[0], F_SETFD, FD_CLOEXEC) < 0) ||
      (fcntl(des[1], F_SETFD, FD_CLOEXEC) < 0)) {
    return 0;
  }


  *p = des[1];
  return 1;
}
