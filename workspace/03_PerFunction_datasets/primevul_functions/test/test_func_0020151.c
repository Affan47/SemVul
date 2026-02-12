subshell_exit (s)
     int s;
{
  fflush (stdout);
  fflush (stderr);


  if (signal_is_trapped (0))
    s = run_exit_trap ();

  sh_exit (s);
}
