vec_compare(const void *av, const void *bv)
{
    const struct vector *a = *(const struct vector **)av;
    const struct vector *b = *(const struct vector **)bv;

    if (a->sizes[MAXCOLOUR] > b->sizes[MAXCOLOUR])
	return -1;
    else if (a->sizes[MAXCOLOUR] < b->sizes[MAXCOLOUR])
	return +1;
    else if (a->want_href < b->want_href)
	return +1;
    else if (a->want_href > b->want_href)
	return -1;
    else if (a->want_href)
	return strcmp(a->name, b->name);
    else if (a->index < b->index)
	return -1;
    else if (a->index > b->index)
	return +1;
    else if (a->essential < b->essential)
	return +1;
    else if (a->essential > b->essential)
	return -1;
    return 0;
}
