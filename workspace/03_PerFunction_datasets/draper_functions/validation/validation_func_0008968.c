Destroy()
{
    DictionaryEntry *t, *n;

    for (int i = 0; i < tableLength; i++)
    {
	if (table[i] != NULL)
	{
	    t = table[i];
	    do {
	      n = t->next;
	      delete t;
	      t = n;
	    } while (n);
	    table[i] = NULL;
	}
    }
    count = 0;
}
