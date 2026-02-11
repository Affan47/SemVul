rlslist_append(RLSLIST *rlslist, void *datum)

{
  globus_list_t	*l;

  l = NULL;
  if (globus_list_insert(&l, datum) != GLOBUS_SUCCESS)
    return GLOBUS_RLS_NOMEMORY;
  if (!rlslist->list)
    rlslist->list = l;
  else
    rlslist->last->next = l;
  rlslist->last = l;
  return GLOBUS_RLS_SUCCESS;
}
