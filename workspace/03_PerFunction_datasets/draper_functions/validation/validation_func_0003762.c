bldAddRecovDictRecs(
	FDB *						pDb,
	REBUILD_STATE *		pRebuildState,
	RECOV_DICT_INFO **	ppDictListRV,
	FLMBOOL *				pbStartedTransRV)
{
	RECOV_DICT_INFO *	pDict;

	if( (pDict = *ppDictListRV) != NULL)
	{
		*ppDictListRV = NULL;
		return bldDoDict( pDb, pRebuildState, pDict,	pbStartedTransRV);
	}

	return FERR_OK;
}
