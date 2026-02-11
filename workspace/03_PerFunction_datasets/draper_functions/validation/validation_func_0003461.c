copyField(
	F_Session *	pFlmSession,
	HFDB				hDb,
	const char *	pszDbKey,
	FLMUINT			uiDrn,
	FLMUINT			uiContainer,
	FLMBOOL			bReadOnly)
{
	RCODE				rc = FERR_OK;
	FlmRecord *		pRec = NULL;
	char				szTmp[ 128];
	void *			pvOrigField = NULL;
	void *			pvMarkerField = NULL;
	char *			pTmp = &szTmp[0];
	FLMUINT			uiFldCnt;
	FLMUINT			uiSelectedField;
	FLMUINT			uiLoop;


	if (RC_BAD( rc = constructRecord( uiDrn, uiContainer, &pRec, hDb)))
	{
		goto Exit;
	}


	if (RC_BAD( rc = getFormValueByName( "FieldCount", &pTmp, sizeof( szTmp), NULL)))
	{
		displayRecordPage( pFlmSession, hDb, pszDbKey, pRec, bReadOnly, rc);
		goto Exit;
	}
	uiFldCnt = f_atoud( szTmp);

	if (uiFldCnt == 1)
	{
		uiSelectedField = 0;
	}
	else
	{

		if (RC_BAD( rc = getFormValueByName( "radioSel", &pTmp, sizeof( szTmp), NULL)))
		{
			displayRecordPage( pFlmSession, hDb, pszDbKey, pRec, bReadOnly, rc);
			goto Exit;
		}
		uiSelectedField = f_atoud( szTmp);
	}


	pvOrigField = pRec->root();


	for ( uiLoop = 0; uiLoop < uiSelectedField; uiLoop++)
	{
		pvOrigField = pRec->next( pvOrigField);
	}


	pvMarkerField = pRec->nextSibling( pvOrigField);

	if (!pRec->isLast( pvOrigField) && pvMarkerField == NULL && !pRec->hasChild( pvOrigField))
	{
		pvMarkerField = pRec->next( pvOrigField);
	}


	if (RC_BAD( rc = copyFieldsFromTo( pRec, pvOrigField, pvMarkerField)))
	{
		displayRecordPage( pFlmSession, hDb, pszDbKey, pRec, bReadOnly, rc);
		goto Exit;
	}


	displayRecordPage( pFlmSession, hDb, pszDbKey, pRec, bReadOnly, rc);

Exit:

	if( pRec)
	{
		pRec->Release();
	}

	return;
}
