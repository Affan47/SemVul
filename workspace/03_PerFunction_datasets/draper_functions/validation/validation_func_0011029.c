initializeShutdownHandlers() {
#ifndef MINGW
  struct sigaction sig;
  struct sigaction oldsig;
#endif

  if (shutdown_signal != NULL)
    abort();
  shutdown_signal = SEMAPHORE_NEW(0);
  shutdown_active = 0;
#ifndef MINGW
  sig.sa_handler = &run_shutdown;
  sigemptyset(&sig.sa_mask);
#ifdef SA_INTERRUPT
  sig.sa_flags = SA_INTERRUPT;
#else
  sig.sa_flags = SA_RESTART;
#endif
  sigaction(SIGINT,  &sig, &oldsig);
  sigaction(SIGTERM, &sig, &oldsig);
  sigaction(SIGQUIT, &sig, &oldsig);
#else
  SetConsoleCtrlHandler(&run_shutdown_win, TRUE);
#endif
}
