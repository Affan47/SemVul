chkResolveIXMissingKey(
	STATE_INFO *		pStateInfo,
	IX_CHK_INFO *		pIxChkInfo)
{
	RCODE					rc = FERR_OK;
	FLMBOOL				bKeyInRec;
	FLMBOOL				bKeyInIndex;
	FLMBOOL				bFixCorruption = FALSE;
	RS_IX_KEY *			pCurrRSKey = pIxChkInfo->pCurrRSKey;


	if (RC_BAD( rc = chkGetKeySource( pStateInfo, pIxChkInfo,
				  pCurrRSKey->uiRSIxNum, &(pCurrRSKey->pucRSKeyBuf[RS_KEY_OFFSET]),
				  (FLMUINT) (pCurrRSKey->uiRSKeyLen - RS_KEY_OVERHEAD),
				  pCurrRSKey->uiRSRefDrn, NULL, &bKeyInRec, &bKeyInIndex)))
	{
		if (rc == FERR_INDEX_OFFLINE)
		{
			rc = FERR_OK;
		}

		goto Exit;
	}


	if (!bKeyInRec || bKeyInIndex)
	{
		pIxChkInfo->pDbInfo->pProgress->ui64NumConflicts++;
		goto Exit;
	}


	pIxChkInfo->pDbInfo->pProgress->ui64NumRecKeysNotFound++;
	pIxChkInfo->pDbInfo->pProgress->uiLogicalIndexCorruptions++;


	if (RC_BAD( rc = chkReportIxError( pStateInfo, pIxChkInfo,
				  FLM_DRN_NOT_IN_KEY_REFSET, pCurrRSKey->uiRSIxNum,
				  pCurrRSKey->uiRSRefDrn, &(pCurrRSKey->pucRSKeyBuf[RS_KEY_OFFSET]),
				  (FLMUINT) (pCurrRSKey->uiRSKeyLen - RS_KEY_OVERHEAD),
				  &bFixCorruption)))
	{
		goto Exit;
	}


	if (!bFixCorruption)
	{


		pIxChkInfo->pDbInfo->pProgress->bLogicalIndexCorrupt = TRUE;
		goto Exit;
	}


	pIxChkInfo->pDbInfo->pProgress->uiLogicalIndexRepairs++;


	if (RC_OK( rc = chkAddDelKeyRef( pStateInfo, pIxChkInfo,
				 pCurrRSKey->uiRSIxNum, &(pCurrRSKey->pucRSKeyBuf[RS_KEY_OFFSET]),
				 (FLMUINT) (pCurrRSKey->uiRSKeyLen - RS_KEY_OVERHEAD),
				 pCurrRSKey->uiRSRefDrn, 0)))
	{
		pIxChkInfo->pDbInfo->bReposition = TRUE;
		goto Exit;
	}
	else
	{
		if (rc == FERR_NOT_UNIQUE)
		{


			if (RC_OK( rc = chkResolveNonUniqueKey( pStateInfo, pIxChkInfo,
						 pCurrRSKey->uiRSIxNum,
						 &(pCurrRSKey->pucRSKeyBuf[RS_KEY_OFFSET]),
						 (FLMUINT) (pCurrRSKey->uiRSKeyLen - RS_KEY_OVERHEAD),
						 pCurrRSKey->uiRSRefDrn)))
			{
				pIxChkInfo->pDbInfo->bReposition = TRUE;
				goto Exit;
			}
		}
		else
		{


			pIxChkInfo->pDbInfo->pProgress->bLogicalIndexCorrupt = TRUE;
		}
	}

Exit:

	return (rc);
}
