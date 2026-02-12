unsigned CjfifDecode::DecodeApp2IccProfile(unsigned nLen)
{
	CString		strTmp;
	unsigned	nMarkerSeqNum;
	unsigned	nNumMarkers;
	unsigned	nPayloadLen;

	unsigned	nMarkerPosStart;

	nMarkerSeqNum = Buf(m_nPos++);
	nNumMarkers = Buf(m_nPos++);
	nPayloadLen = nLen - 2 - 12 - 2;

	strTmp.Format(_T("      Marker Number = %u of %u"),nMarkerSeqNum,nNumMarkers);
	m_pLog->AddLine(strTmp);

	if (nMarkerSeqNum == 1) {
		nMarkerPosStart = m_nPos;
		DecodeIccHeader(nMarkerPosStart);
	} else {
		m_pLog->AddLineWarn(_T("      Only support decode of 1st ICC Marker"));
	}

	return 0;
}
