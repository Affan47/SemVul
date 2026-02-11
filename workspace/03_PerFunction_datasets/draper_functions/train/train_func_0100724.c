ginBuildCallback(Relation index, HeapTuple htup, Datum *values,
				 bool *isnull, bool tupleIsAlive, void *state)
{

	GinBuildState *buildstate = (GinBuildState *) state;
	MemoryContext oldCtx;

	if (*isnull)
		return;

	oldCtx = MemoryContextSwitchTo(buildstate->tmpCtx);

	buildstate->indtuples += ginHeapTupleBulkInsert(buildstate, *values, &htup->t_self);


	if (buildstate->accum.allocatedMemory >= maintenance_work_mem * 1024L / 2L ||
		buildstate->accum.maxdepth > GIN_MAX_TREE_DEPTH)
	{
		ItemPointerData *list;
		Datum		entry;
		uint32		nlist;

		while ((list = ginGetEntry(&buildstate->accum, &entry, &nlist)) != NULL)
			ginEntryInsert(index, &buildstate->ginstate, entry, list, nlist, TRUE);

		MemoryContextReset(buildstate->tmpCtx);
		ginInitBA(&buildstate->accum);
	}

	MemoryContextSwitchTo(oldCtx);
}
