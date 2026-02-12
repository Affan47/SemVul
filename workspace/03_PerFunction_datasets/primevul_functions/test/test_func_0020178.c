wskipname (pat, dname, flags)
     wchar_t *pat, *dname;
     int flags;
{
  if (glob_always_skip_dot_and_dotdot && WDOT_OR_DOTDOT (dname))
    return 1;


  if (noglob_dot_filenames == 0 && pat[0] != L'.' &&
	(pat[0] != L'\\' || pat[1] != L'.') &&
	WDOT_OR_DOTDOT (dname))
    return 1;


 else if (noglob_dot_filenames && dname[0] == L'.' &&
	pat[0] != L'.' &&
	   (pat[0] != L'\\' || pat[1] != L'.'))
    return 1;

  return 0;
}
