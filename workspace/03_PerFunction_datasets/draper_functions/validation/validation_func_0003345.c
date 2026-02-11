decode_table_max_word_nr (decode_table *entry)
{
  int max_word_nr = 0;
  while (entry != NULL)
    {
      decode_cond *cond;
      if (entry->word_nr > max_word_nr)
	max_word_nr = entry->word_nr;
      for (cond = entry->conditions; cond != NULL; cond = cond->next)
	{
	  if (cond->word_nr > max_word_nr)
	    max_word_nr = cond->word_nr;
	}
      entry = entry->next;
    }
  return max_word_nr;
}
