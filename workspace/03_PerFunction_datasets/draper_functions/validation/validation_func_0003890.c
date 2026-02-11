assoc_to_word_list_internal (h, t)
     HASH_TABLE *h;
     int t;
{
  WORD_LIST *list;
  int i;
  BUCKET_CONTENTS *tlist;
  char *w;

  if (h == 0 || assoc_empty (h))
    return((WORD_LIST *)NULL);
  list = (WORD_LIST *)NULL;

  for (i = 0; i < h->nbuckets; i++)
    for (tlist = hash_items (i, h); tlist; tlist = tlist->next)
      {
	w = (t == 0) ? (char *)tlist->data : (char *)tlist->key;
	list = make_word_list (make_bare_word(w), list);
      }
  return (REVERSE_LIST(list, WORD_LIST *));
}
