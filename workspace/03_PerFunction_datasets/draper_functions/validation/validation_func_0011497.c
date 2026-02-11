reset_terminating_signals ()
{
  register int i;
#if defined (HAVE_POSIX_SIGNALS)
  struct sigaction act;
#endif

  if (termsigs_initialized == 0)
    return;

#if defined (HAVE_POSIX_SIGNALS)
  act.sa_flags = 0;
  sigemptyset (&act.sa_mask);
  for (i = 0; i < TERMSIGS_LENGTH; i++)
    {


      if (signal_is_trapped (XSIG (i)) || signal_is_special (XSIG (i)))
	continue;

      act.sa_handler = XHANDLER (i);
      act.sa_flags = XSAFLAGS (i);
      sigaction (XSIG (i), &act, (struct sigaction *) NULL);
    }
#else
  for (i = 0; i < TERMSIGS_LENGTH; i++)
    {
      if (signal_is_trapped (XSIG (i)) || signal_is_special (XSIG (i)))
	continue;

      signal (XSIG (i), XHANDLER (i));
    }
#endif
}
