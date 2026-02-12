void CjfifDecode::PrepareSignatureSingle(bool bRotate)
{
	CStringA			strTmp;
	CStringA			strSet;

	CStringA			strHashIn;
	unsigned char		pHashIn[2000];
	CStringA			strDqt;
	MD5_CTX				sMd5;
	unsigned			nLenHashIn;
	unsigned			nInd;

	ASSERT(m_eImgLandscape!=ENUM_LANDSCAPE_UNSET);


	bool bDqtDefined = false;
	for (unsigned nSet=0;nSet<4;nSet++) {
		if (m_abImgDqtSet[nSet]) {
			bDqtDefined = true;
		}
	}
	if (!bDqtDefined) {
		m_strHash = _T("NONE");
		m_strHashRot = _T("NONE");
		return;
	}


	if (DB_SIG_VER == 0x00) {
		strHashIn = "";
	} else {
		strHashIn = "JPEGsnoop";
	}


	for (unsigned nSet=0;nSet<4;nSet++) {
		if (m_abImgDqtSet[nSet]) {
			strSet = "";
			strSet.Format("*DQT%u,",nSet);
			strHashIn += strSet;
			for (unsigned i=0;i<64;i++) {
				nInd = (!bRotate)?i:glb_anQuantRotate[i];
				strTmp.Format("%03u,",m_anImgDqtTbl[nSet][nInd]);
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
		m_strHash.Format(_T("%08X%08X%08X%08X"),sMd5.digest32[0],sMd5.digest32[1],sMd5.digest32[2],sMd5.digest32[3]);
	} else {
		m_strHashRot.Format(_T("%08X%08X%08X%08X"),sMd5.digest32[0],sMd5.digest32[1],sMd5.digest32[2],sMd5.digest32[3]);
	}

}
