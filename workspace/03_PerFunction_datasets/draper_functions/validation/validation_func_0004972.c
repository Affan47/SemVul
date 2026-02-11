useEnd(void)
{
	XAP_Dialog_AppPersistent::useEnd();

	FREEP(m_szDocumentTitle);
	FREEP(m_szDocumentPathname);
	FREEP(m_szPrintToFilePathname);
	FREEP(m_pageSize);

	if (m_answer == a_OK)
	{
		m_bPersistValid = true;
		m_persistNrCopies = m_nCopies;
		m_persistCollate = m_bCollate;
		m_persistColorSpace = m_cColorSpace;
		m_persistPrintToFile = m_bDoPrintToFile;
	}


}
