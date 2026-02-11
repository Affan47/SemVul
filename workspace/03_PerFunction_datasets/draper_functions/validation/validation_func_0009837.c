find_user_entry(struct user_entry_type *et,
                                   struct userrec *u)
{
  struct user_entry **e, *t;

  for (e = &(u->entries); *e; e = &((*e)->next)) {
    if (((*e)->type == et) ||
        ((*e)->name && !egg_strcasecmp((*e)->name, et->name))) {
      t = *e;
      *e = t->next;
      t->next = u->entries;
      u->entries = t;
      return t;
    }
  }
  return NULL;
}
