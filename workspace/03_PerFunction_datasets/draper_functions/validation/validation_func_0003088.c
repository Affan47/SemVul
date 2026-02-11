KYAddUniqueKeys(
	FDB *				pDb)
{
	RCODE				rc = FERR_OK;
	KREF_CNTRL *	pKrefCntrl = &pDb->KrefCntrl;
	KREF_ENTRY **	pKrefTbl = pKrefCntrl->pKrefTbl;
	KREF_ENTRY *	pKref;
	FLMUINT			uiCurKrefNum;
	FLMUINT			uiPrevKrefNum;
	FLMUINT			uiTargetCount;
	FLMUINT			uiLastIxNum;
	LFILE *			pLFile;
	FLMBOOL			bUniqueErrorHit = FALSE;


	flmAssert( !(pDb->uiFlags & FDB_BACKGROUND_INDEXING));


	for (uiCurKrefNum = pKrefCntrl->uiLastRecEnd, uiLastIxNum = 0,
			  uiTargetCount = pKrefCntrl->uiCount; uiCurKrefNum < uiTargetCount;)
	{
		pKref = pKrefTbl[uiCurKrefNum];

		if (pKref->uiFlags & KREF_UNIQUE_KEY)
		{
			flmAssert( pKref->ui16IxNum > 0 &&
						  pKref->ui16IxNum < FLM_UNREGISTERED_TAGS);

			if (pKref->ui16IxNum != uiLastIxNum)
			{
				uiLastIxNum = pKref->ui16IxNum;
				if (RC_BAD( rc = fdictGetIndex( pDb->pDict,
							  pDb->pFile->bInLimitedMode, uiLastIxNum, &pLFile, NULL)))
				{


					flmAssert( rc != FERR_INDEX_OFFLINE);
					goto Exit;
				}
			}


			if (RC_BAD( rc = FSRefUpdate( pDb, pLFile, pKref)))
			{
				pDb->Diag.uiInfoFlags |= FLM_DIAG_INDEX_NUM;
				pDb->Diag.uiIndexNum = pKref->ui16IxNum;


				if (rc != FERR_NOT_UNIQUE)
				{
					goto Exit;
				}

				bUniqueErrorHit = TRUE;


				uiTargetCount = uiCurKrefNum;
				uiCurKrefNum = pKrefCntrl->uiLastRecEnd;


				continue;
			}


			pKref->uiFlags ^= KREF_DELETE_FLAG;
		}

		uiCurKrefNum++;
	}

	if (bUniqueErrorHit)
	{
		rc = RC_SET( FERR_NOT_UNIQUE);
		pKrefCntrl->uiCount = pKrefCntrl->uiLastRecEnd;
	}
	else
	{


		for (uiCurKrefNum = uiPrevKrefNum = pKrefCntrl->uiLastRecEnd,
				  uiTargetCount = pKrefCntrl->uiCount;
				  uiCurKrefNum < uiTargetCount; uiCurKrefNum++)
		{
			pKref = pKrefTbl[uiCurKrefNum];

			if (!(pKref->uiFlags & KREF_UNIQUE_KEY))
			{
				pKrefTbl[uiPrevKrefNum++] = pKrefTbl[uiCurKrefNum];
			}
		}

		pKrefCntrl->uiCount = uiPrevKrefNum;
	}

Exit:

	return (rc);
}
