bool CjfifDecode::DecodeMakerSubType()
{
	CString strTmp;

	m_nImgExifMakeSubtype = 0;

	if (m_strImgExifMake == _T("NIKON"))
	{
		strTmp = _T("");
		for (unsigned nInd=0;nInd<5;nInd++) {
			strTmp += (char)Buf(m_nPos+nInd);
		}

		if (strTmp == _T("Nikon")) {
			if (Buf(m_nPos+6) == 1) {

				m_pLog->AddLine(_T("    Nikon Makernote Type 1 detected"));
				m_nImgExifMakeSubtype = 1;
				m_nPos += 8;
			} else if (Buf(m_nPos+6) == 2) {

				m_pLog->AddLine(_T("    Nikon Makernote Type 3 detected"));
				m_nImgExifMakeSubtype = 3;
				m_nPos += 18;
			} else {
				CString strTmp = _T("ERROR: Unknown Nikon Makernote Type");
				m_pLog->AddLineErr(strTmp);
				if (m_pAppConfig->bInteractive)
					AfxMessageBox(strTmp);
				return FALSE;
			}
		} else {

			m_pLog->AddLine(_T("    Nikon Makernote Type 2 detected"));


			m_nImgExifMakeSubtype = 1;
			m_nPos += 0;
		}

	}
	else if (m_strImgExifMake == _T("SIGMA"))
	{
		strTmp = _T("");
		for (unsigned ind=0;ind<8;ind++) {
			if (Buf(m_nPos+ind) != 0)
				strTmp += (char)Buf(m_nPos+ind);
		}
		if ( (strTmp == _T("SIGMA")) ||
			(strTmp == _T("FOVEON"))  )
		{


			m_nPos += 10;
		} else {
			CString strTmp = _T("ERROR: Unknown SIGMA Makernote identifier");
			m_pLog->AddLineErr(strTmp);
			if (m_pAppConfig->bInteractive)
				AfxMessageBox(strTmp);
			return FALSE;
		}

	}
	else if (m_strImgExifMake == _T("FUJIFILM"))
	{
		strTmp = _T("");
		for (unsigned ind=0;ind<8;ind++) {
			if (Buf(m_nPos+ind) != 0)
				strTmp += (char)Buf(m_nPos+ind);
		}
		if (strTmp == _T("FUJIFILM"))
		{


			m_nPos += 12;
		} else {
			CString strTmp = _T("ERROR: Unknown FUJIFILM Makernote identifier");
			m_pLog->AddLineErr(strTmp);
			if (m_pAppConfig->bInteractive)
				AfxMessageBox(strTmp);
			return FALSE;
		}

	}
	else if (m_strImgExifMake == _T("SONY"))
	{
		strTmp = _T("");
		for (unsigned ind=0;ind<12;ind++) {
			if (Buf(m_nPos+ind) != 0)
				strTmp += (char)Buf(m_nPos+ind);
		}
		if (strTmp == _T("SONY DSC "))
		{


			m_nPos += 12;
		} else {
			CString strTmp = _T("ERROR: Unknown SONY Makernote identifier");
			m_pLog->AddLineErr(strTmp);
			if (m_pAppConfig->bInteractive)
				AfxMessageBox(strTmp);
			return FALSE;
		}

	}


	return TRUE;

}
