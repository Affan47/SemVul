freeelem(Cell *ap, char *s)
{
	Array *tp;
	Cell *p, *prev = NULL;
	int h;

	tp = (Array *) ap->sval;
	h = hash(s, tp->size);
	for (p = tp->tab[h]; p != NULL; prev = p, p = p->cnext)
		if (strcmp(s, p->nval) == 0) {
			if (prev == NULL)
				tp->tab[h] = p->cnext;
			else
				prev->cnext = p->cnext;
			if (freeable(p))
				xfree(p->sval);
			free(p->nval);
			free(p);
			tp->nelem--;
			return;
		}
}
