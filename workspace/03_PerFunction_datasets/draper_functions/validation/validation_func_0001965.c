duplicate_list_elem(t_list * list, void * (*duplicate)(void *))
{
  t_list *	newlist;

  newlist = NULL;
  if (list)
    {
      list->cur = list->begin;
      while (list->cur)
        {
	  if (!(put_in_list(&newlist,
			    (duplicate ?
			     duplicate(list->cur->data)
			     : list->cur->data))))
	    return (NULL);
          list->cur = list->cur->next;
        }
    }
  return (newlist);
}
