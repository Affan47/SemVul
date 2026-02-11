close( void)
{
	flmAssert( m_bSetupCalled);

	if( m_pMultiFileHdl)
	{
		m_pMultiFileHdl->Release();
		m_pMultiFileHdl = NULL;
	}

	if( m_pFileHdl)
	{
		m_pFileHdl->Release();
		m_pFileHdl = NULL;
	}

	m_bOpen = FALSE;
	m_ui64Offset = 0;

	return( FERR_OK);
}
