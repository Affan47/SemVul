safe_list_append(edge_t * e, elist * L)
{
    int i;

    for (i = 0; i < L->size; i++)
	if (e == L->list[i])
	    return;
    elist_append(e, (*L));
}
