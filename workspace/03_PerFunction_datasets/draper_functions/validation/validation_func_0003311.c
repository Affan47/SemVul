watch_find_hash(const char *name)
{
  dlink_node *ptr = NULL;

  DLINK_FOREACH(ptr, watchTable[strhash(name)].head)
  {
    struct Watch *anptr = ptr->data;

    if (!irccmp(anptr->nick, name))
      return anptr;
  }

  return NULL;
}
