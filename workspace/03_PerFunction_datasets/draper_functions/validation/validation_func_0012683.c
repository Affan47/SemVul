gistBuildCallback(Relation index,
				  HeapTuple htup,
				  Datum *values,
				  bool *isnull,
				  bool tupleIsAlive,
				  void *state)
{
	GISTBuildState *buildstate = (GISTBuildState *) state;
	IndexTuple	itup;
	MemoryContext oldCtx;

	oldCtx = MemoryContextSwitchTo(buildstate->giststate->tempCxt);


	itup = gistFormTuple(buildstate->giststate, index, values, isnull, true);
	itup->t_tid = htup->t_self;

	if (buildstate->bufferingMode == GIST_BUFFERING_ACTIVE)
	{

		gistBufferingBuildInsert(buildstate, itup);
	}
	else
	{


		gistdoinsert(index, itup, buildstate->freespace,
					 buildstate->giststate);
	}


	buildstate->indtuples += 1;
	buildstate->indtuplesSize += IndexTupleSize(itup);

	MemoryContextSwitchTo(oldCtx);
	MemoryContextReset(buildstate->giststate->tempCxt);

	if (buildstate->bufferingMode == GIST_BUFFERING_ACTIVE &&
		buildstate->indtuples % BUFFERING_MODE_TUPLE_SIZE_STATS_TARGET == 0)
	{

		buildstate->gfbb->pagesPerBuffer =
			calculatePagesPerBuffer(buildstate, buildstate->gfbb->levelStep);
	}


	if ((buildstate->bufferingMode == GIST_BUFFERING_AUTO &&
		 buildstate->indtuples % BUFFERING_MODE_SWITCH_CHECK_STEP == 0 &&
		 effective_cache_size < smgrnblocks(index->rd_smgr, MAIN_FORKNUM)) ||
		(buildstate->bufferingMode == GIST_BUFFERING_STATS &&
		 buildstate->indtuples >= BUFFERING_MODE_TUPLE_SIZE_STATS_TARGET))
	{


		gistInitBuffering(buildstate);
	}
}
