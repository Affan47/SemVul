spginsert(PG_FUNCTION_ARGS)
{
	Relation	index = (Relation) PG_GETARG_POINTER(0);
	Datum	   *values = (Datum *) PG_GETARG_POINTER(1);
	bool	   *isnull = (bool *) PG_GETARG_POINTER(2);
	ItemPointer ht_ctid = (ItemPointer) PG_GETARG_POINTER(3);

#ifdef NOT_USED
	Relation	heapRel = (Relation) PG_GETARG_POINTER(4);
	IndexUniqueCheck checkUnique = (IndexUniqueCheck) PG_GETARG_INT32(5);
#endif
	SpGistState spgstate;
	MemoryContext oldCtx;
	MemoryContext insertCtx;

	insertCtx = AllocSetContextCreate(CurrentMemoryContext,
									  "SP-GiST insert temporary context",
									  ALLOCSET_DEFAULT_MINSIZE,
									  ALLOCSET_DEFAULT_INITSIZE,
									  ALLOCSET_DEFAULT_MAXSIZE);
	oldCtx = MemoryContextSwitchTo(insertCtx);

	initSpGistState(&spgstate, index);


	while (!spgdoinsert(index, &spgstate, ht_ctid, *values, *isnull))
	{
		MemoryContextReset(insertCtx);
		initSpGistState(&spgstate, index);
	}

	SpGistUpdateMetaPage(index);

	MemoryContextSwitchTo(oldCtx);
	MemoryContextDelete(insertCtx);


	PG_RETURN_BOOL(false);
}
