initialize (void)
{
  char *file, *env_sysrc;
  bool ok = true;


  env_sysrc = getenv ("SYSTEM_WGETRC");
  if (env_sysrc && file_exists_p (env_sysrc))
    {
      ok &= run_wgetrc (env_sysrc);


      if (! ok)
        {
          fprintf (stderr, _("\
Parsing system wgetrc file (env SYSTEM_WGETRC) failed.  Please check\n\
'%s',\n\
or specify a different file using --config.\n"), env_sysrc);
          exit (WGET_EXIT_PARSE_ERROR);
        }
    }

#ifdef SYSTEM_WGETRC
  else if (file_exists_p (SYSTEM_WGETRC))
    ok &= run_wgetrc (SYSTEM_WGETRC);


  if (! ok)
    {
      fprintf (stderr, _("\
Parsing system wgetrc file failed.  Please check\n\
'%s',\n\
or specify a different file using --config.\n"), SYSTEM_WGETRC);
      exit (WGET_EXIT_PARSE_ERROR);
    }
#endif

  file = wgetrc_file_name ();
  if (!file)
    return;


#ifdef SYSTEM_WGETRC
  if (!strcmp (file, SYSTEM_WGETRC))
    {
      fprintf (stderr, _("\
%s: Warning: Both system and user wgetrc point to %s.\n"),
               exec_name, quote (file));
    }
  else
#endif
    ok &= run_wgetrc (file);


  if (!ok)
    exit (WGET_EXIT_PARSE_ERROR);

  xfree (file);
  return;
}
