count_defs (cpp_reader *pfile ATTRIBUTE_UNUSED, cpp_hashnode *hn, void *ss_p)
{
  struct cpp_savedstate *const ss = (struct cpp_savedstate *)ss_p;

  switch (hn->type)
    {
    case NT_MACRO:
      if (hn->flags & NODE_BUILTIN)
	return 1;


    case NT_VOID:
      {
	struct cpp_string news;
	void **slot;

	news.len = NODE_LEN (hn);
	news.text = NODE_NAME (hn);
	slot = htab_find (ss->definedhash, &news);
	if (slot == NULL)
	  {
	    ss->hashsize += NODE_LEN (hn) + 1;
	    ss->n_defs += 1;
	  }
      }
      return 1;

    case NT_ASSERTION:

      return 1;

    default:
      abort ();
    }
}
