trapVector (
	int		 sig,
	siginfo_t	*siginfo,
	void		*truc)
{
  printf ("\n");
  (void) printGlobalStatistics();
  if (sig == SIGINT)
  {
    printf ("Catch SIGINT - exit...\n");
    fflush (stdout);
    ldcltExit (mctx.exitStatus);
  }
  return;
}
