bool CjfifDecode::ExpectMarkerEnd(unsigned long nMarkerStart,unsigned nMarkerLen)
{
	CString			strTmp;
	unsigned long	nMarkerEnd = nMarkerStart + nMarkerLen;
	unsigned long	nMarkerExtra = nMarkerEnd - m_nPos;
	if (m_nPos < nMarkerEnd) {

		strTmp.Format(_T("  WARNING: Marker length longer than expected"));
		m_pLog->AddLineWarn(strTmp);
		if (!m_pAppConfig->bRelaxedParsing) {

			m_pLog->AddLineErr(_T("  Stopping decode"));
			m_pLog->AddLineErr(_T("  Use [Img Search Fwd/Rev] to locate other valid embedded JPEGs"));
			return false;
		} else {

			strTmp.Format(_T("  Skipping remainder [%u bytes]"),nMarkerExtra);
			m_pLog->AddLineWarn(strTmp);
			m_nPos += nMarkerExtra;
		}
	} else if (m_nPos > nMarkerEnd) {

		strTmp.Format(_T("  WARNING: Marker length shorter than expected"));
		m_pLog->AddLineWarn(strTmp);
		if (!m_pAppConfig->bRelaxedParsing) {

			m_pLog->AddLineErr(_T("  Stopping decode"));
			m_pLog->AddLineErr(_T("  Use [Img Search Fwd/Rev] to locate other valid embedded JPEGs"));
			return false;
		} else {


			if (Buf(m_nPos) == 0xFF) {

				m_pLog->AddLineWarn(_T("  Resuming decode"));
			} else if (Buf(nMarkerEnd) == 0xFF) {

				m_nPos = nMarkerEnd;
				m_pLog->AddLineWarn(_T("  Rolling back pointer to end indicated by length"));
				m_pLog->AddLineWarn(_T("  Resuming decode"));
			} else {

				m_pLog->AddLineWarn(_T("  Resuming decode"));
			}
		}
	}


	return true;
}
