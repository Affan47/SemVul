flmFreeDictList(
	FDICT **		ppDictRV)
{
	FDICT *		pTmp;
	FDICT *		pDict = *ppDictRV;

	while (pDict)
	{
		pTmp = pDict;
		pDict = pDict->pNext;
		flmFreeDict( pTmp);
	}

	*ppDictRV = NULL;
}
