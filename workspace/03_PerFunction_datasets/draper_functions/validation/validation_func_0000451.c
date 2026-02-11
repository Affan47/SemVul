push_token_on_list (token_t * tokenlist, script_t * scriptbuf,
		    char *start, size_t len)
{
  token_t *me, *next;
  if (len == 0)
    return (tokenlist);

  me = (token_t *) xmalloc (sizeof (token_t));

  if (tokenlist == NULL)
    {
      next = NULL;
    }
  else
    {
      next = tokenlist->next;
      tokenlist->next = me;
    }

  me->next = next;
  me->script = scriptbuf;
  me->buf = start;
  me->len = len;

  return (me);
}
