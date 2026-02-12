void CjfifDecode::PrepareSignatureThumbSingle(bool bRotate)
{
	CStringA			strTmp;
	CStringA			strSet;

	CStringA			strHashIn;
	unsigned char		pHashIn[2000];
	CStringA			strDqt;
	MD5_CTX				sMd5;
	unsigned			nLenHashIn;
	unsigned			nInd;


	bool bDqtDefined = false;
	for (unsigned nSet=0;nSet<4;nSet++) {
		if (m_abImgDqtThumbSet[nSet]) {
			bDqtDefined = true;
		}
	}
	if (!bDqtDefined) {
		m_strHashThumb = _T("NONE");
		m_strHashThumbRot = _T("NONE");
		return;
	}

	if (DB_SIG_VER == 0x00) {
		strHashIn = _T("");
	} else {
		strHashIn = _T("JPEGsnoop");
	}


	for (unsigned nSet=0;nSet<4;nSet++) {
		if (m_abImgDqtThumbSet[nSet]) {
			strSet = "";
			strSet.Format("*DQT%u,",nSet);
			strHashIn += strSet;
			for (unsigned i=0;i<64;i++) {
				nInd = (!bRotate)?i:glb_anQuantRotate[i];
				strTmp.Format("%03u,",m_anImgThumbDqt[nSet][nInd]);
				strHashIn += strTmp;
			}
		}
	}


	if (DB_SIG_VER == 0x00) {
		strHashIn += "*CSS,";
		strHashIn += m_strImgQuantCss;
		strHashIn += ",";
	}
	strHashIn += "*END";
	nLenHashIn = strlen(strHashIn);


	for (unsigned i=0;i<nLenHashIn;i+=80) {
		strTmp = "";
		strTmp.Format("In%u: [",i/80);
		strTmp += strHashIn.Mid(i,80);
		strTmp += "]";
#ifdef DEBUG_SIG
		m_pLog->AddLine(strTmp);
#endif
	}


	ASSERT(nLenHashIn < 2000);
	for (unsigned i=0;i<nLenHashIn;i++) {
		pHashIn[i] = strHashIn.GetAt(i);
	}


	MD5Init(&sMd5, 0);
	MD5Update(&sMd5, pHashIn, nLenHashIn);
	MD5Final(&sMd5);


	sMd5.digest32[0] = (sMd5.digest32[0] & 0x00FFFFFF) + (DB_SIG_VER << 24);


	if (!bRotate) {
		m_strHashThumb.Format(_T("%08X%08X%08X%08X"),sMd5.digest32[0],sMd5.digest32[1],sMd5.digest32[2],sMd5.digest32[3]);
	} else {
		m_strHashThumbRot.Format(_T("%08X%08X%08X%08X"),sMd5.digest32[0],sMd5.digest32[1],sMd5.digest32[2],sMd5.digest32[3]);
	}

}
