waitdaemon_timeout (int signo _GL_UNUSED_PARAMETER)
{
  int left;

  left = alarm (0);
  signal (SIGALRM, SIG_DFL);
  if (left == 0)
    error (EXIT_FAILURE, 0, "timed out waiting for child");
}
