FlmCursorTestRec(
	HFCURSOR			hCursor,
	FlmRecord * 	pRec,
	FLMBOOL * 		pbIsMatch)
{
	RCODE				rc = FERR_OK;
	FDB *				pDb = NULL;
	CURSOR *			pCursor = (CURSOR *)hCursor;
	SUBQUERY *		pSubQuery;

	flmAssert( pCursor != NULL);
	*pbIsMatch = FALSE;

	if (pCursor->pCSContext)
	{
		rc = flmCurCSTestRec( pCursor, 0, pRec, pbIsMatch);
		goto Exit2;
	}


	if (pCursor->QTInfo.uiNestLvl ||
		 ((pCursor->QTInfo.uiExpecting & FLM_Q_OPERAND) &&
			 pCursor->QTInfo.pTopNode))
	{
		rc = RC_SET( FERR_CURSOR_SYNTAX);
		goto Exit;
	}


	if (!pCursor->bOptimized)
	{
		if (RC_BAD( rc = flmCurPrep( pCursor)))
		{
			goto Exit;
		}
	}

	flmAssert( pCursor->pDb != NULL);

	pDb = pCursor->pDb;
	if (RC_BAD( rc = flmCurDbInit( pCursor)))
	{
		goto Exit;
	}


	flmAssert( pRec->getContainerID() != 0);

	pSubQuery = pCursor->pSubQueryList;
	while (pSubQuery)
	{
		FLMUINT	uiResult;

		if (RC_BAD( rc = flmCurEvalCriteria( pCursor, pSubQuery,
									pRec, FALSE, &uiResult)))
		{
			goto Exit;
		}
		if (uiResult == FLM_TRUE)
		{
			*pbIsMatch = TRUE;
			break;
		}
		pSubQuery = pSubQuery->pNext;
	}

Exit:

	if (pDb)
	{
		fdbExit( pDb);
	}

Exit2:

	return( rc);
}
