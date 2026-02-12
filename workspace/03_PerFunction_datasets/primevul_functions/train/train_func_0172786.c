void CjfifDecode::ProcessFile(CFile* inFile)
{

	CString strTmp;


	Reset();


	if (m_pImgSrcDirty) {
		m_pImgDec->ResetState();
	}


	if (m_pStatBar) {
		m_pStatBar->SetPaneText(0,_T("Processing..."));
	}


	ULONGLONG	nPosFileEnd;
	nPosFileEnd = inFile->GetLength();
	if (nPosFileEnd > 0xFFFFFFFFUL) {
		CString strTmp = _T("File too large. Skipping.");
		m_pLog->AddLineErr(strTmp);
		if (m_pAppConfig->bInteractive)
			AfxMessageBox(strTmp);
		return;
	}
	m_nPosFileEnd = static_cast<unsigned long>(nPosFileEnd);


	unsigned nStartPos;
	nStartPos = m_pAppConfig->nPosStart;
	m_nPos = nStartPos;
	m_nPosEmbedStart = nStartPos;

	strTmp.Format(_T("Start Offset: 0x%08X"),nStartPos);
	m_pLog->AddLine(strTmp);


	DecodeAvi();


	unsigned	nWidth=0;
	unsigned	nHeight=0;

#ifdef PS_IMG_DEC_EN


	bool bDecPsdOk;
	bDecPsdOk = m_pPsDec->DecodePsd(nStartPos,&m_pImgDec->m_pDibTemp,nWidth,nHeight);
	if (bDecPsdOk) {

		m_pImgDec->m_bDibTempReady = true;
		m_pImgDec->m_bPreviewIsJpeg = false;
		m_pImgDec->SetImageDimensions(nWidth,nHeight);


		m_pImgDec->SetImageDetails(0,0,0,0,false,0);


		return;
	}
#else

	if (m_pPsDec->DecodePsd(nStartPos,NULL,nWidth,nHeight)) {
		return;
	}
#endif


#ifdef SUPPORT_DICOM


	bool			bDicom = false;
	unsigned long	nPosJpeg = 0;
	bDicom = m_pDecDicom->DecodeDicom(0,m_nPosFileEnd,nPosJpeg);
	if (bDicom) {

		if (nStartPos == 0) {
			m_pAppConfig->nPosStart = nPosJpeg;

			nStartPos = m_pAppConfig->nPosStart;
			m_nPos = nStartPos;
			m_nPosEmbedStart = nStartPos;

			strTmp.Format(_T("Adjusting Start Offset to: 0x%08X"),nStartPos);
			m_pLog->AddLine(strTmp);
			m_pLog->AddLine(_T(""));
		}
	}
#endif


	if (m_pAppConfig->nPosStart!=0) {
		strTmp.Format(_T("[Offset]=[%lu],"),m_pAppConfig->nPosStart);
        m_strImgExtras += strTmp;
	}

	unsigned nDataAfterEof = 0;

	BOOL bDone = FALSE;
	while (!bDone)
	{


		if (DecodeMarker() != DECMARK_OK) {
			bDone = TRUE;
			if (m_nPosFileEnd >= m_nPosEoi) {
				nDataAfterEof = m_nPosFileEnd - m_nPosEoi;
			}
		} else {
			if (m_nPos > m_pWBuf->GetPosEof()) {
				m_pLog->AddLineErr(_T("ERROR: Early EOF - file may be missing EOI"));
				bDone = TRUE;
			}
		}
	}


	m_strImgQuantCss = _T("?x?");
	m_strHash = _T("NONE");
	m_strHashRot = _T("NONE");

	if (m_bImgOK) {
		ASSERT(m_eImgLandscape!=ENUM_LANDSCAPE_UNSET);

		if (m_nSofNumComps_Nf == NUM_CHAN_YCC) {


			unsigned	nCompIdent = m_anSofQuantCompId[SCAN_COMP_CB];
			unsigned	nCssFactH = m_nSofHorzSampFactMax_Hmax/m_anSofHorzSampFact_Hi[nCompIdent];
			unsigned	nCssFactV = m_nSofVertSampFactMax_Vmax/m_anSofVertSampFact_Vi[nCompIdent];
			if (m_eImgLandscape!=ENUM_LANDSCAPE_NO) {

				m_strImgQuantCss.Format(_T("%ux%u"),nCssFactH,nCssFactV);
			}
			else {

				m_strImgQuantCss.Format(_T("%ux%u"),nCssFactV,nCssFactH);
			}
		} else if (m_nSofNumComps_Nf == NUM_CHAN_GRAYSCALE) {
			m_strImgQuantCss = _T("Gray");
		}

		DecodeEmbeddedThumb();


		PrepareSignature();


		if (m_pAppConfig->bSigSearch) {


			if (m_strHash == _T("NONE")) {
				m_pLog->AddLineWarn(_T("Skipping compression signature search as no DQT"));
			} else {
				CompareSignature();
			}
		}

		if (nDataAfterEof > 0) {
			m_pLog->AddLine(_T(""));
			m_pLog->AddLineHdr(_T("*** Additional Info ***"));
			strTmp.Format(_T("NOTE: Data exists after EOF, range: 0x%08X-0x%08X (%u bytes)"),
				m_nPosEoi,m_nPosFileEnd,nDataAfterEof);
			m_pLog->AddLine(strTmp);
		}


		OutputSpecial();
	}


	if (m_pStatBar) {
		m_pStatBar->SetPaneText(0,_T("Done"));
	}


}
