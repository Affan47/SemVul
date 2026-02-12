unsigned CjfifDecode::DecodeApp13Ps()
{


	CString			strTmp;
	CString			strBimName;
	bool			bDone = false;

	unsigned		nVal = 0x8000;
	unsigned		nSaveFormat = 0;

	CString			strVal;
	CString			strByte;

	CString			strBimSig;


	m_pPsDec->Reset();

	while (!bDone)
	{


		strBimSig = m_pWBuf->BufReadStrn(m_nPos,4);

		if (strBimSig == _T("8BIM")) {
			m_pPsDec->PhotoshopParseImageResourceBlock(m_nPos,3);
		} else {

			bDone = true;
		}
	}


	m_nImgQualPhotoshopSa = m_pPsDec->m_nQualitySaveAs;
	m_nImgQualPhotoshopSfw = m_pPsDec->m_nQualitySaveForWeb;
	m_bPsd = m_pPsDec->m_bPsd;

	return 0;
}
