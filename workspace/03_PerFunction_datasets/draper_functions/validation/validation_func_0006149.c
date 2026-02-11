sl_destroy(skiplist *l)
{
	node p, q;

	if (!l || !l->header)
		return;

	p = l->header;
	q = p->forward[0];
	free(p);
	p = q;

	while (p != NULL)
	{
		q = p->forward[0];

		int j;

		for (j = 0; j < p->nbr; j++)
		{
			if (l->freekey)
				l->freekey(p->bkt[j].key);

			if (l->freeval)
				l->freeval(p->bkt[j].val);
		}

		free(p);
		p = q;
	}

	free(l);
}
