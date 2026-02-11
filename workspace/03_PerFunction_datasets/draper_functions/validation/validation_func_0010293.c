DXMap(Object g_in, Object map, char *srcComponent, char *dstComponent)
{
    Object   result;
    Type     type;
    Category cat;
    int	     rank, shape[32];


    switch(DXGetObjectClass(map))
    {
	case CLASS_ARRAY:
	case CLASS_FIELD:
	case CLASS_XFORM:
	case CLASS_INTERPOLATOR:
	    break;

	case CLASS_GROUP:
	    if (DXGetGroupClass((Group)map) == CLASS_COMPOSITEFIELD ||
		DXGetGroupClass((Group)map) == CLASS_MULTIGRID)
		break;

	default:
	    DXSetError(ERROR_DATA_INVALID, "map type invalid");
	    return NULL;
    }

    if (DXGetObjectClass(g_in) == CLASS_ARRAY)
    {

	if (DXGetObjectClass(map) == CLASS_ARRAY)
	{
	    int	     nItems;

	    if (! DXGetArrayInfo((Array)map, &nItems, &type, &cat, &rank, shape))
		return NULL;

	    if (nItems != 1)
	    {
		DXSetError(ERROR_DATA_INVALID, "constant array size != 1");
		return NULL;
	    }

	    if (! DXGetArrayInfo((Array)g_in, &nItems, NULL, NULL, NULL, NULL))
		return NULL;

	    if (nItems <= 0)
	    {
		DXSetError(ERROR_DATA_INVALID, "index array length < 1");
		return NULL;
	    }

	    result = (Object)DXNewConstantArrayV(nItems,
			DXGetArrayData((Array)map), type, cat, rank, shape);

	    return result;
	}
	else
	{
	    Interpolator mapInterp;

	    if (DXGetObjectClass(map) != CLASS_INTERPOLATOR)
	    {
		mapInterp = DXNewInterpolator(map, INTERP_INIT_DELAY, -1.0);
		if (! mapInterp)
		{
		    DXAddMessage("unable to interpolate in map");
		    return NULL;
		}

		DXReference((Object)mapInterp);

		result = (Object)DXMapArray((Array)g_in, mapInterp, NULL);

		DXDelete((Object)mapInterp);
	    }
	    else
		result = (Object)DXMapArray((Array)g_in, (Interpolator)map, NULL);

	    return result;
	}
    }
    else
    {
	result = g_in;

#ifdef PARALLEL
	DXCreateTaskGroup();
#endif

	if (! Map_Object(result, map, srcComponent, dstComponent))
	{
	    DXAddMessage("mapping function failed");
#ifdef PARALLEL
	    DXAbortTaskGroup();
#endif
	    return NULL;
	}

#ifdef PARALLEL
	DXExecuteTaskGroup();
#endif


	if (! strcmp(dstComponent, "data"))
	{
	    Type	type;
	    Category	cat;
	    int		rank, shape[MAX_SHAPE];

	    if (! DXGetMapType(map, &type, &cat, &rank, shape))
		return NULL;

	    if (! SetGroupTypeVRecursive(result, type, cat, rank, shape))
		return NULL;
	}
    }

    return result;
}
