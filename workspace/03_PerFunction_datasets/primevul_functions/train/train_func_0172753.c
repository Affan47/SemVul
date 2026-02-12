CString CjfifDecode::PrintAsHex32(unsigned* anWords,unsigned nCount)
{
	CString strVal;
	CString strFull;
	strFull = _T("0x[");
	unsigned nMaxDisplay = MAX_anValues/4;
	bool bExceedMaxDisplay;
	bExceedMaxDisplay = (nCount > nMaxDisplay);
	for (unsigned nInd=0;nInd<nCount;nInd++)
	{
		if (nInd < nMaxDisplay) {
			if (nInd == 0) {

			} else {

				strFull += _T(" ");
			}

			strVal.Format(_T("%08X"),anWords[nInd]);
			strFull += strVal;
		}

		if ((nInd == nMaxDisplay) && (bExceedMaxDisplay)) {
			strFull += _T("...");
		}

	}
	strFull += _T("]");
	return strFull;
}
