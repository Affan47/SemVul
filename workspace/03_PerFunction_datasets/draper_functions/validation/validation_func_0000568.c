print_index_and_element (len, ind, list)
      int len, ind;
      WORD_LIST *list;
{
  register WORD_LIST *l;
  register int i;

  if (list == 0)
    return (0);
  for (i = ind, l = list; l && --i; l = l->next)
    ;
  fprintf (stderr, "%*d%s%s", len, ind, RP_SPACE, l->word->word);
  return (STRLEN (l->word->word));
}
