bool CjfifDecode::ExportJpegDo(CString strFileIn, CString strFileOut,
			unsigned long nFileLen, bool bOverlayEn,bool bDhtAviInsert,bool bForceSoi,bool bForceEoi)
{
	CFile*		pFileOutput;
	CString		strTmp = _T("");

	strTmp.Format(_T("  Exporting to:   [%s]"),(LPCTSTR)strFileOut);
	m_pLog->AddLine(strTmp);

	if (strFileIn == strFileOut) {
		strTmp.Format(_T("ERROR: Can't overwrite source file. Aborting export."));
		m_pLog->AddLineErr(strTmp);
		if (m_pAppConfig->bInteractive)
			AfxMessageBox(strTmp);

		return false;
	}

	ASSERT(strFileIn != _T(""));
	if (strFileIn == _T("")) {
		strTmp.Format(_T("ERROR: Export but source filename empty"));
		m_pLog->AddLineErr(strTmp);
		if (m_pAppConfig->bInteractive)
			AfxMessageBox(strTmp);

		return false;
	}


	try
	{


		pFileOutput = new CFile(strFileOut, CFile::modeCreate| CFile::modeWrite | CFile::typeBinary | CFile::shareDenyNone);
	}
	catch (CFileException* e)
	{
		TCHAR msg[MAX_BUF_EX_ERR_MSG];
		CString strError;
		e->GetErrorMessage(msg,MAX_BUF_EX_ERR_MSG);
		e->Delete();
		strError.Format(_T("ERROR: Couldn't open file for write [%s]: [%s]"),
			(LPCTSTR)strFileOut, (LPCTSTR)msg);
		m_pLog->AddLineErr(strError);
		if (m_pAppConfig->bInteractive)
			AfxMessageBox(strError);
		pFileOutput = NULL;

		return false;

	}


	if (nFileLen==0) {
		strTmp.Format(_T("ERROR: Source file length error. Please Reprocess first."));
		m_pLog->AddLineErr(strTmp);
		if (m_pAppConfig->bInteractive)
			AfxMessageBox(strTmp);

		if (pFileOutput) { delete pFileOutput; pFileOutput = NULL; }
		return false;
	}


	unsigned		nCopyStart;
	unsigned		nCopyEnd;
	unsigned		nCopyLeft;
	unsigned		ind;

	BYTE*			pBuf;

	pBuf = new BYTE[EXPORT_BUF_SIZE+10];
	if (!pBuf) {
		if (pFileOutput) { delete pFileOutput; pFileOutput = NULL; }
		return false;
	}


	if (!m_bStateSoi && bForceSoi) {
		m_pLog->AddLine(_T("    Forcing SOI Marker"));
		BYTE	anBufSoi[2] = {0xFF,JFIF_SOI};
		pFileOutput->Write(&anBufSoi,2);
	}

	nCopyStart = m_nPosEmbedStart;
	nCopyEnd   = (m_nPosSos-1);
	ind = nCopyStart;
	while (ind<nCopyEnd) {
		nCopyLeft = nCopyEnd-ind+1;
		if (nCopyLeft>EXPORT_BUF_SIZE) { nCopyLeft = EXPORT_BUF_SIZE; }
		for (unsigned ind1=0;ind1<nCopyLeft;ind1++) {
			pBuf[ind1] = Buf(ind+ind1,!bOverlayEn);
		}
		pFileOutput->Write(pBuf,nCopyLeft);
		ind += nCopyLeft;

		ASSERT(nFileLen>0);
		strTmp.Format(_T("Exporting %3u%%..."),ind*100/nFileLen);
		SetStatusText(strTmp);
	}


	if (bDhtAviInsert) {

		strTmp.Format(_T("  Inserting standard AVI DHT huffman table"));
		m_pLog->AddLine(strTmp);
		pFileOutput->Write(m_abMJPGDHTSeg,JFIF_DHT_FAKE_SZ);
	}


	nCopyStart = m_nPosSos;
	nCopyEnd   = m_nPosEmbedEnd-1;
	ind = nCopyStart;
	while (ind<nCopyEnd) {
		nCopyLeft = nCopyEnd-ind+1;
		if (nCopyLeft>EXPORT_BUF_SIZE) { nCopyLeft = EXPORT_BUF_SIZE; }
		for (unsigned ind1=0;ind1<nCopyLeft;ind1++) {
			pBuf[ind1] = Buf(ind+ind1,!bOverlayEn);
		}
		pFileOutput->Write(pBuf,nCopyLeft);
		ind += nCopyLeft;

		ASSERT(nFileLen>0);
		strTmp.Format(_T("Exporting %3u%%..."),ind*100/nFileLen);
		SetStatusText(strTmp);
	}


	if (bForceEoi) {
		m_pLog->AddLine(_T("    Forcing EOI Marker"));
		BYTE	anBufEoi[2] = {0xFF,JFIF_EOI};
		pFileOutput->Write(&anBufEoi,2);
	}


	pFileOutput->Close();

	if (pBuf) {
		delete [] pBuf;
		pBuf = NULL;
	}

	if (pFileOutput) {
		delete pFileOutput;
		pFileOutput = NULL;
	}

	SetStatusText(_T(""));
	strTmp.Format(_T("  Export done"));
	m_pLog->AddLine(strTmp);

	return true;
}
