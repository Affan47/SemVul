extglob_skipname (pat, dname, flags)
     char *pat, *dname;
     int flags;
{
  char *pp, *pe, *t, *se;
  int n, r, negate, wild, nullpat;

  negate = *pat == '!';
  wild = *pat == '*' || *pat == '?';
  pp = pat + 2;
  se = pp + strlen (pp) - 1;
  pe = glob_patscan (pp, se, 0);

  if (pe == 0)
    return 0;


  if (pe == se && *pe == ')' && (t = strchr (pp, '|')) == 0)
    {
      *pe = '\0';
#if defined (HANDLE_MULTIBYTE)
      r = mbskipname (pp, dname, flags);
#else
      r = skipname (pp, dname, flags);
#endif
      *pe = ')';
      if (wild && pe[1])
        return (skipname (pe+1, dname, flags));
      return r;
    }


  nullpat = pe >= (pat + 2) && pe[-2] == '(' && pe[-1] == ')';


  while (t = glob_patscan (pp, pe, '|'))
    {
      n = t[-1];
      if (extglob_pattern_p (pp) && n == ')')
	t[-1] = n;
      else
	t[-1] = '\0';
#if defined (HANDLE_MULTIBYTE)
      r = mbskipname (pp, dname, flags);
#else
      r = skipname (pp, dname, flags);
#endif
      t[-1] = n;
      if (r == 0)
        return r;
      pp = t;
    }


  if (pp == se)
    return r;


  if (wild && *pe)
    return (skipname (pe, dname, flags));
  return 1;
}
