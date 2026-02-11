clear(
	FLMBOOL			bReleaseMemory)
{
	RCODE		rc = FERR_OK;

	if( isCached())
	{
		flmAssert( 0);
		rc = RC_SET( FERR_ILLEGAL_OP);
		goto Exit;
	}

	if( bReleaseMemory)
	{
		if( m_pucBuffer)
		{
			gv_FlmSysData.RCacheMgr.pRecBufAlloc->freeBuf(
				m_uiBufferSize, &m_pucBuffer);
		}

		m_uiBufferSize = 0;
		m_uiFldTblSize = 0;
	}

	if (m_pucFieldIdTable)
	{
		gv_FlmSysData.RCacheMgr.pRecBufAlloc->freeBuf(
			fieldIdTableByteSize(), &m_pucFieldIdTable);
	}
	m_uiFlags = 0;
	m_uiContainerID = 0;
	m_uiRecordID = 0;
	m_uiFldTblOffset = 0;
	m_uiDataBufOffset = 0;
	m_uiFirstAvail = 0;
	m_uiAvailFields = 0;
	m_bHolesInData = FALSE;

Exit:

	return( rc);
}
