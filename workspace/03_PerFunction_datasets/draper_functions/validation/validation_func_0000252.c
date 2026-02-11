LE_Compl_Add_Word(char *word, int word_length)
{
  CompNode **p;
  CompNode *q;
  int cmp;

  for (p = &comp_start; *p; p = &(*p)->next)
    {
      cmp = strcmp((*p)->word, word);
      if (cmp == 0)
	return word;

      if (cmp > 0)
	break;
    }

  if ((q = (CompNode *) malloc(sizeof(CompNode))) == NULL)
    exit(1);

  q->word = word;
  q->word_length = word_length;
  q->next = *p;
  *p = q;

  return word;
}
