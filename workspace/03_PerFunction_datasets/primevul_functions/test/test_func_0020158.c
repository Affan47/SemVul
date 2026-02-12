skipname (pat, dname, flags)
     char *pat;
     char *dname;
     int flags;
{
#if EXTENDED_GLOB
  if (extglob_pattern_p (pat))
    return (extglob_skipname (pat, dname, flags));
#endif

  if (glob_always_skip_dot_and_dotdot && DOT_OR_DOTDOT (dname))
    return 1;


  if (noglob_dot_filenames == 0 && pat[0] != '.' &&
	(pat[0] != '\\' || pat[1] != '.') &&
	DOT_OR_DOTDOT (dname))
    return 1;


  else if (noglob_dot_filenames && dname[0] == '.' && pat[0] != '.' &&
	(pat[0] != '\\' || pat[1] != '.'))
    return 1;

  return 0;
}
