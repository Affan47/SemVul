get_list(void)
{
  struct list *p;

  list_gets++;
  if (list_avail == NULL)
    p = (struct list *) tp_alloc((int) sizeof(struct list));
  else {
    list_avails--;
    p = list_avail;
    list_avail = (struct list *) list_avail->first_cl;
  }
  p->first_cl = NULL;
  p->last_cl = NULL;
  p->name[0] = '\0';
  return(p);
}
