signal_handler (int signal)
{
#ifdef DEBUG
  printf ("signal_handler\n");
#endif

  switch (signal)
    {
    case SIGHUP:
      do_update = 1;
      break;
    case SIGINT:
    case SIGTERM:
      quit ();
      break;
    case SIGCHLD:
      wait (NULL);
      break;
    }
}
