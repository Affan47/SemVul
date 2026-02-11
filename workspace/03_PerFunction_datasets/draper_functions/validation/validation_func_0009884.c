changeState(
	FLMUINT		uiFieldID,
	FLMUINT		uiNewState)
{
	RCODE			rc = FERR_OK;
	FLMBOOL		bRestartTrans = FALSE;

	if( m_puiStateTbl[ uiFieldID] != ITT_FLD_STATE_CHECKING)
	{
		return( RC_SET( FERR_FAILURE));
	}

	if( m_bInternalTrans)
	{
		if( m_pDb->uiTransType != FLM_NO_TRANS)
		{
			(void)flmAbortDbTrans( m_pDb);
			bRestartTrans = TRUE;
		}
	}


	m_puiStateTbl[ uiFieldID] = 0;


	if( RC_BAD( rc = flmChangeItemState( m_pDb, uiFieldID, uiNewState)))
	{
		goto Exit;
	}


	if( bRestartTrans)
	{
		flmAssert( m_bInternalTrans);

		if( RC_BAD( rc = flmBeginDbTrans( m_pDb, FLM_READ_TRANS,
								0, FLM_DONT_POISON_CACHE)))
		{
			goto Exit;
		}
	}

Exit:

	return( rc);
}
