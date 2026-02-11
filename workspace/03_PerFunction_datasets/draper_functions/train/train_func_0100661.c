ginFillScanKey(GinScanOpaque so, OffsetNumber attnum,
			   StrategyNumber strategy, int32 searchMode,
			   Datum query, uint32 nQueryValues,
			   Datum *queryValues, GinNullCategory *queryCategories,
			   bool *partial_matches, Pointer *extra_data)
{
	GinScanKey	key = &(so->keys[so->nkeys++]);
	GinState   *ginstate = &so->ginstate;
	uint32		nUserQueryValues = nQueryValues;
	uint32		i;


	if (searchMode != GIN_SEARCH_MODE_DEFAULT)
		nQueryValues++;
	key->nentries = nQueryValues;
	key->nuserentries = nUserQueryValues;

	key->scanEntry = (GinScanEntry *) palloc(sizeof(GinScanEntry) * nQueryValues);
	key->entryRes = (bool *) palloc0(sizeof(bool) * nQueryValues);

	key->query = query;
	key->queryValues = queryValues;
	key->queryCategories = queryCategories;
	key->extra_data = extra_data;
	key->strategy = strategy;
	key->searchMode = searchMode;
	key->attnum = attnum;

	ItemPointerSetMin(&key->curItem);
	key->curItemMatches = false;
	key->recheckCurItem = false;
	key->isFinished = false;

	for (i = 0; i < nQueryValues; i++)
	{
		Datum		queryKey;
		GinNullCategory queryCategory;
		bool		isPartialMatch;
		Pointer		this_extra;

		if (i < nUserQueryValues)
		{

			queryKey = queryValues[i];
			queryCategory = queryCategories[i];
			isPartialMatch =
				(ginstate->canPartialMatch[attnum - 1] && partial_matches)
				? partial_matches[i] : false;
			this_extra = (extra_data) ? extra_data[i] : NULL;
		}
		else
		{

			queryKey = (Datum) 0;
			switch (searchMode)
			{
				case GIN_SEARCH_MODE_INCLUDE_EMPTY:
					queryCategory = GIN_CAT_EMPTY_ITEM;
					break;
				case GIN_SEARCH_MODE_ALL:
					queryCategory = GIN_CAT_EMPTY_QUERY;
					break;
				case GIN_SEARCH_MODE_EVERYTHING:
					queryCategory = GIN_CAT_EMPTY_QUERY;
					break;
				default:
					elog(ERROR, "unexpected searchMode: %d", searchMode);
					queryCategory = 0;
					break;
			}
			isPartialMatch = false;
			this_extra = NULL;


			strategy = InvalidStrategy;
		}

		key->scanEntry[i] = ginFillScanEntry(so, attnum,
											 strategy, searchMode,
											 queryKey, queryCategory,
											 isPartialMatch, this_extra);
	}
}
