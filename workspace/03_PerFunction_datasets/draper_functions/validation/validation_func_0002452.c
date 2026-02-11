qprodterms(Object o)
{
    int i, count;
    Group g = NULL;
    Array *terms = NULL;

    CHECKARRAYIF(o, CLASS_PRODUCTARRAY, "product array");

    if (!DXGetProductArrayInfo((ProductArray)o, &count, NULL))
	return NULL;

    terms = (Array *)DXAllocate(count * sizeof(Array));
    if (!terms)
	return NULL;

    if (!DXGetProductArrayInfo((ProductArray)o, &count, terms))
	goto error;

    g = DXNewGroup();
    if (!g)
	goto error;

    for (i=0; i < count; i++)
	if (!DXSetMember(g, NULL, (Object)terms[i]))
	    goto error;

    DXFree((Pointer)terms);
    return (Object)g;

  error:
    DXFree((Pointer)terms);
    DXDelete((Object)g);
    return NULL;
}
