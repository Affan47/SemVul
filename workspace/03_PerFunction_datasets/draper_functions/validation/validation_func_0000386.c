bamInsertOffset(AjPTable h, ajint bin, ajulong beg,
				   ajulong end)
{
    bam_binlist_t *l = NULL;
    int* tmp = NULL;

    l = ajTableFetchmodV(h, &bin);

    if (!l)
    {
	AJNEW0(l);
	l->m = 1;
	l->n = 0;
	l->list = (pair64_t*)calloc(l->m, 16);

	AJNEW0(tmp);
	*tmp = bin;

	ajTablePut(h, tmp, l);
    }

    if (l->n == l->m)
    {
	l->m <<= 1;
	l->list = (pair64_t*)realloc(l->list, l->m * 16);
    }

    l->list[l->n].u = beg;
    l->list[l->n++].v = end;
}
