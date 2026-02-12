fix_assignment_words (words)
     WORD_LIST *words;
{
  WORD_LIST *w, *wcmd;
  struct builtin *b;
  int assoc;

  if (words == 0)
    return;

  b = 0;
  assoc = 0;

  wcmd = words;
  for (w = words; w; w = w->next)
    if (w->word->flags & W_ASSIGNMENT)
      {
	if (b == 0)
	  {


	    while (posixly_correct && wcmd && wcmd->word && wcmd->word->word && STREQ (wcmd->word->word, "command"))
	      wcmd = wcmd->next;
	    b = builtin_address_internal (wcmd->word->word, 0);
	    if (b == 0 || (b->flags & ASSIGNMENT_BUILTIN) == 0)
	      return;
	    else if (b && (b->flags & ASSIGNMENT_BUILTIN))
	      wcmd->word->flags |= W_ASSNBLTIN;
	  }
	w->word->flags |= (W_NOSPLIT|W_NOGLOB|W_TILDEEXP|W_ASSIGNARG);
#if defined (ARRAY_VARS)
	if (assoc)
	  w->word->flags |= W_ASSIGNASSOC;
#endif
      }
#if defined (ARRAY_VARS)


    else if (w->word->word[0] == '-' && strchr (w->word->word, 'A'))
      {
	if (b == 0)
	  {
	    while (posixly_correct && wcmd && wcmd->word && wcmd->word->word && STREQ (wcmd->word->word, "command"))
	      wcmd = wcmd->next;
	    b = builtin_address_internal (wcmd->word->word, 0);
	    if (b == 0 || (b->flags & ASSIGNMENT_BUILTIN) == 0)
	      return;
	    else if (b && (b->flags & ASSIGNMENT_BUILTIN))
	      wcmd->word->flags |= W_ASSNBLTIN;
	  }
	if (wcmd->word->flags & W_ASSNBLTIN)
	  assoc = 1;
      }
#endif
}
