kwsinit (kwset_t *kwset)
{
  static char trans[NCHAR];
  int i;

  if (match_icase && MB_CUR_MAX == 1)
    {
      for (i = 0; i < NCHAR; ++i)
        trans[i] = tolower (i);

      *kwset = kwsalloc (trans);
    }
  else
    *kwset = kwsalloc (NULL);

  if (!*kwset)
    xalloc_die ();
}
