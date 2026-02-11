firstRec(
	FDB *				pDb,
	FlmRecord **	ppRecord,
	FLMUINT *		puiRecordId)
{
	RCODE				rc;

	if( RC_BAD( rc = checkTransaction( pDb)))
	{
		goto Exit;
	}
	m_pCurSet = m_pFirstSet;
	if( !m_pCurSet)
	{
		m_bAtBOF = FALSE;
		m_bAtEOF = TRUE;
		rc = RC_SET( FERR_EOF_HIT);
		goto Exit;
	}

	m_bAtBOF = m_bAtEOF = FALSE;
	m_curRecPos.uiRecordId = 0;
	for(;;)
	{
		if( m_curRecPos.uiRecordId < m_pCurSet->fromKey.uiRecordId)
		{
			if( RC_BAD( rc = setRecPosition( pDb, TRUE,
				&m_pCurSet->fromKey, &m_curRecPos)))
			{
				if( rc == FERR_BOF_HIT)
				{
					rc = RC_SET( FERR_EOF_HIT);
				}
				m_bAtEOF = TRUE;
				goto Exit;
			}
		}


		if( m_curRecPos.uiRecordId <= m_pCurSet->untilKey.uiRecordId)
		{
			break;
		}
		if( !m_pCurSet->pNext)
		{
			m_bAtEOF = TRUE;
			rc = FERR_EOF_HIT;
			goto Exit;
		}
		m_pCurSet = m_pCurSet->pNext;
	}


	if( puiRecordId)
	{
		*puiRecordId = m_curRecPos.uiRecordId;
	}
	if( ppRecord)
	{
		if( RC_BAD( rc = flmRcaRetrieveRec( pDb, NULL, m_uiContainer,
				m_curRecPos.uiRecordId, TRUE, m_curRecPos.pStack,
				m_pLFile, ppRecord)))
		{
			goto Exit;
		}
	}

Exit:

	return( rc);
}
