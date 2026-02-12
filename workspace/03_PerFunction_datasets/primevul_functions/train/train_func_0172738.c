CString CjfifDecode::PrintAsHexUC(unsigned char* anBytes,unsigned nCount)
{
	CString strVal;
	CString strFull;
	strFull = _T("0x[");
	unsigned nMaxDisplay = MAX_anValues;
	bool bExceedMaxDisplay;
	bExceedMaxDisplay = (nCount > nMaxDisplay);
	for (unsigned nInd=0;nInd<nCount;nInd++)
	{
		if (nInd < nMaxDisplay) {
			if ((nInd % 4) == 0) {
				if (nInd == 0) {

				} else {

					strFull += _T(" ");
				}
			} else {

			}

			strVal.Format(_T("%02X"),anBytes[nInd]);
			strFull += strVal;
		}

		if ((nInd == nMaxDisplay) && (bExceedMaxDisplay)) {
			strFull += _T("...");
		}

	}
	strFull += _T("]");
	return strFull;
}
