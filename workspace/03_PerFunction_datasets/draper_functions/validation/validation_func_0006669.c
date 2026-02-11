addcnstarrays(StackParms *sp, StackInfo *si, char *component)
{
    Array newarr = NULL;
    Array a;
    int j;
    Object o;
    Type t0;
    Category c0;
    int rank0;
    int shape0[MAXRANK];
    int size, items;
    Pointer *dvalue0 = NULL;
    Pointer *dvalue1 = NULL;


    for (j=0; (o=DXGetSeriesMember((Series)si->thisobj, j, NULL)); j++) {

	a = (Array)DXGetComponentValue((Field)o, component);

	if ((DXGetArrayClass(a) != CLASS_CONSTANTARRAY) &&
	    (DXGetArrayClass(a) != CLASS_REGULARARRAY))
	    return NULL;

    }


    a = (Array)DXGetComponentValue(si->f0, component);
    if (DXGetArrayClass(a) == CLASS_CONSTANTARRAY) {

	if (!DXGetArrayInfo(a, &items, &t0, &c0, &rank0, NULL))
	    return NULL;

	if (rank0 >= MAXRANK)
	    return NULL;

	if (!DXGetArrayInfo(a, NULL, NULL, NULL, &rank0, shape0))
	    return NULL;

	size = DXGetItemSize(a);

	dvalue0 = (Pointer)DXAllocate(size);
	dvalue1 = (Pointer)DXAllocate(size);
	if (!dvalue0 || !dvalue1)
	    return NULL;

	if (!DXQueryConstantArray(a, NULL, (Pointer)dvalue0))
	    goto error;

	for (j=1; (o=DXGetSeriesMember((Series)si->thisobj, j, NULL)); j++) {

	    a = (Array)DXGetComponentValue((Field)o, component);

	    if (DXGetArrayClass(a) != CLASS_CONSTANTARRAY)
		goto error;

	    if (!DXQueryConstantArray(a, NULL, (Pointer)dvalue1))
		goto error;

	    if (memcmp(dvalue0, dvalue1, size) != 0)
		goto error;
	}


	newarr = (Array)DXNewConstantArrayV(items * si->membercnt,
					    (Pointer)dvalue0,
					    t0, c0, rank0, shape0);
	if (!newarr)
	    goto error;

	goto done;
    }


    if (DXGetArrayClass(a) == CLASS_REGULARARRAY) {


	return NULL;
    }


  done:
    return newarr;

  error:
    DXFree(dvalue0);
    DXFree(dvalue1);
    DXDelete((Object)newarr);
    return NULL;
}
