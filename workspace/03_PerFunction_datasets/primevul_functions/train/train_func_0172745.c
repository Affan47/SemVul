CjfifDecode::CjfifDecode(CDocLog* pLog,CwindowBuf* pWBuf,CimgDecode* pImgDec)
{


	CJPEGsnoopApp*	pApp;
	pApp = (CJPEGsnoopApp*)AfxGetApp();
    m_pAppConfig = pApp->m_pAppConfig;
	ASSERT(m_pAppConfig);
	if (DEBUG_EN) m_pAppConfig->DebugLogAdd(_T("CjfifDecode::CjfifDecode() Begin"));

	ASSERT(pLog);
	ASSERT(pWBuf);
	ASSERT(pImgDec);


	m_bOutputDB = FALSE;


	m_bVerbose = FALSE;

	m_pImgSrcDirty = TRUE;


	GenLookupHuffMask();
	if (DEBUG_EN) m_pAppConfig->DebugLogAdd(_T("CjfifDecode::CjfifDecode() Checkpoint 1"));


	m_pStatBar = NULL;


	m_pLog = pLog;
	m_pWBuf = pWBuf;
	m_pImgDec = pImgDec;


	Reset();
	if (DEBUG_EN) m_pAppConfig->DebugLogAdd(_T("CjfifDecode::CjfifDecode() Checkpoint 2"));


	theApp.m_pDbSigs->DatabaseExtraLoad();
	if (DEBUG_EN) m_pAppConfig->DebugLogAdd(_T("CjfifDecode::CjfifDecode() Checkpoint 3"));


	m_pPsDec = new CDecodePs(pWBuf,pLog);
	if (!m_pPsDec) {
		ASSERT(false);
		return;
	}
	if (DEBUG_EN) m_pAppConfig->DebugLogAdd(_T("CjfifDecode::CjfifDecode() Checkpoint 4"));

#ifdef SUPPORT_DICOM

	m_pDecDicom = new CDecodeDicom(pWBuf,pLog);
	if (!m_pDecDicom) {
		ASSERT(false);
		return;
	}
	if (DEBUG_EN) m_pAppConfig->DebugLogAdd(_T("CjfifDecode::CjfifDecode() Checkpoint 5"));
#endif

	if (DEBUG_EN) m_pAppConfig->DebugLogAdd(_T("CjfifDecode::CjfifDecode() End"));
}
