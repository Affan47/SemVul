DXObjectPartition(Object o, int n, int size)
{
    HashTable hTable = NULL;
    HElement *elt;

    hTable = DXCreateHash(sizeof(HElement), Hash, Cmp);
    if (! hTable)
	goto error;


    if (! Pass1(o, hTable))
	goto error;


    DXInitGetNextHashElement(hTable);
    while ((elt = (HElement *)DXGetNextHashElement(hTable)) != NULL)
    {
	if (elt->knt == 1)
	    elt->template = (CompositeField)DXPartition(elt->f, n, size);
	else
	    elt->template = MkPartitionTemplate(elt->f, n, size);

	if (! elt->template)
	    goto error;


	elt->unpart = ((Pointer)elt->template == (Pointer)elt->f);
    }


    o = Pass2(o, hTable);
    if (! o)
	goto error;


    DXInitGetNextHashElement(hTable);
    while ((elt = (HElement *)DXGetNextHashElement(hTable)) != NULL)
	if (elt->knt > 1 && !elt->unpart)
	    DXDelete((Object)elt->template);

    DXDestroyHash(hTable);

    if (! DXEndObject(o))
    {
	DXDelete(o);
	goto error;
    }

    return o;

error:
    DXDestroyHash(hTable);
    return ERROR;
}
