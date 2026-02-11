env_send (const char *var)
{
  register struct env_lst *ep;

  if (my_state_is_wont (TELOPT_NEW_ENVIRON)
#ifdef	OLD_ENVIRON
      && my_state_is_wont (TELOPT_OLD_ENVIRON)
#endif
    )
    {
      fprintf (stderr,
	       "Cannot send '%s': Telnet ENVIRON option not enabled\n", var);
      return;
    }
  ep = env_find (var);
  if (ep == 0)
    {
      fprintf (stderr, "Cannot send '%s': variable not defined\n", var);
      return;
    }
  env_opt_start_info ();
  env_opt_add (ep->var);
  env_opt_end (0);
}
