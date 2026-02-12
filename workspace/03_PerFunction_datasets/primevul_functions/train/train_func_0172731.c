bool CjfifDecode::CompareSignature(bool bQuiet=false)
{
	CString strTmp;
	CString strHashOut;
	CString locationStr;

	unsigned ind;

	bool	bCurXsw = false;
	bool	bCurXmm = false;
	bool	bCurXmkr = false;
	bool	bCurXextrasw = false;
	bool	bCurXcomsw = false;
	bool	bCurXps = false;
	bool	bSrchXsw = false;
	bool	bSrchXswUsig = false;
	bool	bSrchXmmUsig = false;
	bool	bSrchUsig = false;
	bool	bMatchIjg = false;
	CString	sMatchIjgQual = _T("");

	ASSERT(m_strHash != _T("NONE"));
	ASSERT(m_strHashRot != _T("NONE"));

	if (bQuiet) { m_pLog->Disable(); }


	m_pLog->AddLine(_T(""));
	m_pLog->AddLineHdr(_T("*** Searching Compression Signatures ***"));
	m_pLog->AddLine(_T(""));


	strHashOut = _T("  Signature:           ");
	strHashOut += m_strHash;
	m_pLog->AddLine(strHashOut);
	strHashOut = _T("  Signature (Rotated): ");
	strHashOut += m_strHashRot;
	m_pLog->AddLine(strHashOut);

	strTmp.Format(_T("  File Offset:         %lu bytes"),m_pAppConfig->nPosStart);
	m_pLog->AddLine(strTmp);


	strTmp.Format(_T("  Chroma subsampling:  %s"),(LPCTSTR)m_strImgQuantCss);
	m_pLog->AddLine(strTmp);


	strTmp = _T("");
	strTmp.Format(_T("[PS]:[%u/%u],"),m_nImgQualPhotoshopSa,m_nImgQualPhotoshopSfw);
	m_strImgExtras += strTmp;


	if ((m_strImgExifMake == _T("???")) && (m_strImgExifModel == _T("???"))) {
		m_pLog->AddLine(_T("  EXIF Make/Model:     NONE"));
		bCurXmm = false;
	} else {
		strTmp.Format(_T("  EXIF Make/Model:     OK   [%s] [%s]"),(LPCTSTR)m_strImgExifMake,(LPCTSTR)m_strImgExifModel);
		m_pLog->AddLine(strTmp);
		bCurXmm = true;
	}

	if (m_bImgExifMakernotes) {
		m_pLog->AddLine(_T("  EXIF Makernotes:     OK  "));
		bCurXmkr = true;
	} else {
		m_pLog->AddLine(_T("  EXIF Makernotes:     NONE"));
		bCurXmkr = false;
	}

	if (_tcslen(m_strSoftware) == 0) {
		m_pLog->AddLine(_T("  EXIF Software:       NONE"));
		bCurXsw = false;
	} else {
		strTmp.Format(_T("  EXIF Software:       OK   [%s]"),(LPCTSTR)m_strSoftware);
		m_pLog->AddLine(strTmp);


		bCurXsw = true;
	}

	m_pLog->AddLine(_T(""));


	bSrchXswUsig = false;
	bSrchXmmUsig = false;
	bSrchUsig = false;
	bMatchIjg = false;
	sMatchIjgQual = _T("");

	unsigned nSigsInternal = theApp.m_pDbSigs->GetNumSigsInternal();
	unsigned nSigsExtra = theApp.m_pDbSigs->GetNumSigsExtra();

	strTmp.Format(_T("  Searching Compression Signatures: (%u built-in, %u user(*) )"),nSigsInternal,nSigsExtra);
	m_pLog->AddLine(strTmp);


	bool curMatchMm;
	bool curMatchSw;
	bool curMatchSig;
	bool curMatchSigCss;


	if (m_strImgExtras.Find(_T(")[Canon.ImageType]:[CRW:")) != -1) {
		bCurXextrasw = true;
	}
	if (m_strImgExtras.Find(_T("[Nikon1.Quality]:[RAW")) != -1) {
		bCurXextrasw = true;
	}
	if (m_strImgExtras.Find(_T("[Nikon2.Quality]:[RAW")) != -1) {
		bCurXextrasw = true;
	}
	if (m_strImgExtras.Find(_T("[Nikon3.Quality]:[RAW")) != -1) {
		bCurXextrasw = true;
	}
	if ((m_nImgQualPhotoshopSa != 0) || (m_nImgQualPhotoshopSfw != 0)) {
		bCurXps = true;
	}


	if (theApp.m_pDbSigs->SearchCom(m_strComment)) {
		bCurXcomsw = true;
	}

	m_pLog->AddLine(_T(""));
	m_pLog->AddLine(_T("          EXIF.Make / Software        EXIF.Model                            Quality           Subsamp Match?"));
	m_pLog->AddLine(_T("          -------------------------   -----------------------------------   ----------------  --------------"));

	CompSig pEntry;
	unsigned ind_max = theApp.m_pDbSigs->GetDBNumEntries();
	for (ind=0;ind<ind_max;ind++) {
		theApp.m_pDbSigs->GetDBEntry(ind,&pEntry);


		curMatchMm = false;
		curMatchSw = false;
		curMatchSig = false;
		curMatchSigCss = false;


		if ((pEntry.eEditor == ENUM_EDITOR_CAM) &&
			(bCurXmm == true) &&
			(pEntry.strXMake  == m_strImgExifMake) &&
			(pEntry.strXModel == m_strImgExifModel) )
		{
			curMatchMm = true;
		}


		if ((pEntry.eEditor == ENUM_EDITOR_SW) &&
			(bCurXsw == true) &&
			(pEntry.strMSwTrim != _T("")) &&
			(m_strSoftware.Find(pEntry.strMSwTrim) != -1) )
		{

			bSrchXsw = true;
			curMatchSw = true;
		}


		if ( (pEntry.strCSig == m_strHash) || (pEntry.strCSigRot == m_strHash) ||
			(pEntry.strCSig == m_strHashRot) || (pEntry.strCSigRot == m_strHashRot) )
		{
			curMatchSig = true;


			if (pEntry.eEditor == ENUM_EDITOR_SW) {
				bSrchUsig = true;
				curMatchSigCss = true;


				if (pEntry.strMSwDisp == _T("IJG Library")) {
					bMatchIjg = true;
					sMatchIjgQual = pEntry.strUmQual;
				}

			} else {

				if (pEntry.strXSubsamp == m_strImgQuantCss) {
					bSrchUsig = true;
					curMatchSigCss = true;
				} else {
					curMatchSigCss = false;
				}

			}

		} else {

			curMatchSig = false;
			curMatchSigCss = false;
		}


		if (curMatchMm && curMatchSigCss) {
			bSrchXmmUsig = true;
		}

		if (curMatchSw && curMatchSig) {
			bSrchXswUsig = true;
		}

		if (theApp.m_pDbSigs->IsDBEntryUser(ind)) {
			locationStr = _T("*");
		} else {
			locationStr = _T(" ");
		}


		if (curMatchSig) {
			if (pEntry.eEditor==ENUM_EDITOR_CAM) {
				strTmp.Format(_T("    %s%4s[%-25s] [%-35s] [%-16s] %-5s %-5s %-5s"),(LPCTSTR)locationStr,_T("CAM:"),
					(LPCTSTR)pEntry.strXMake.Left(25),(LPCTSTR)pEntry.strXModel.Left(35),(LPCTSTR)pEntry.strUmQual.Left(16),
					(curMatchSigCss?_T("Yes"):_T("No")),_T(""),_T(""));
			} else if (pEntry.eEditor==ENUM_EDITOR_SW) {
				strTmp.Format(_T("    %s%4s[%-25s]  %-35s  [%-16s] %-5s %-5s %-5s"),(LPCTSTR)locationStr,_T("SW :"),
					(LPCTSTR)pEntry.strMSwDisp.Left(25),_T(""),(LPCTSTR)pEntry.strUmQual.Left(16),
					_T(""),_T(""),_T(""));
			} else {
				strTmp.Format(_T("    %s%4s[%-25s] [%-35s] [%-16s] %-5s %-5s %-5s"),(LPCTSTR)locationStr,_T("?? :"),
					(LPCTSTR)pEntry.strXMake.Left(25),(LPCTSTR)pEntry.strXModel.Left(35),(LPCTSTR)pEntry.strUmQual.Left(16),
					_T(""),_T(""),_T(""));
			}
			if (curMatchMm || curMatchSw) {
				m_pLog->AddLineGood(strTmp);
			} else {
				m_pLog->AddLine(strTmp);
			}

		}


	}

	CString strSw;

	if (bMatchIjg) {
		m_pLog->AddLine(_T(""));
		m_pLog->AddLine(_T("    The following IJG-based editors also match this signature:"));
		unsigned nIjgNum;
		CString strIjgSw;
		nIjgNum = theApp.m_pDbSigs->GetIjgNum();
		for (ind=0;ind<nIjgNum;ind++)
		{
			strIjgSw = theApp.m_pDbSigs->GetIjgEntry(ind);
			strTmp.Format(_T("     %4s[%-25s]  %-35s  [%-16s] %-5s %-5s %-5s"),_T("SW :"),
				(LPCTSTR)strIjgSw.Left(25),_T(""),(LPCTSTR)sMatchIjgQual.Left(16),
				_T(""),_T(""),_T(""));
			m_pLog->AddLine(strTmp);
		}
	}


	m_pLog->AddLine(_T(""));

	if (bCurXps) {
		m_pLog->AddLine(_T("  NOTE: Photoshop IRB detected"));
	}
	if (bCurXextrasw) {
		m_pLog->AddLine(_T("  NOTE: Additional EXIF fields indicate software processing"));
	}
	if (bSrchXsw) {
		m_pLog->AddLine(_T("  NOTE: EXIF Software field recognized as from editor"));
	}
	if (bCurXcomsw) {
		m_pLog->AddLine(_T("  NOTE: JFIF COMMENT field is known software"));
	}


	bool bEditDefinite = false;
	bool bEditLikely = false;
	bool bEditNot = false;
	bool bEditNotUnknownSw = false;

	if (bCurXps) {
		bEditDefinite = true;
	}
	if (!bCurXmm) {
		bEditDefinite = true;
	}
	if (bCurXextrasw) {
		bEditDefinite = true;
	}
	if (bCurXcomsw) {
		bEditDefinite = true;
	}
	if (bSrchXsw) {

		bEditDefinite = true;
	}
	if (theApp.m_pDbSigs->LookupExcMmIsEdit(m_strImgExifMake,m_strImgExifModel)) {

		bEditDefinite = true;
	}

	if (!bCurXmkr) {


		if (theApp.m_pDbSigs->LookupExcMmNoMkr(m_strImgExifMake,m_strImgExifModel)) {

		} else {
			bEditLikely = true;
		}
	}


	if (!bEditDefinite && !bEditLikely) {

		if (bSrchXmmUsig) {

			if (!bCurXsw) {


				bEditNot = true;
			} else {


				bEditNot = true;
				bEditNotUnknownSw = true;
			}
		} else {


		}

	}


	m_eImgEdited = EDITED_UNSET;
	if (bEditDefinite) {
		m_eImgEdited = EDITED_YES;
	} else if (bEditLikely) {
		m_eImgEdited = EDITED_YESPROB;
	} else if (bEditNot) {


		m_eImgEdited = EDITED_NO;
	} else {


		m_eImgEdited = EDITED_UNSURE;
	}


	if (m_pAppConfig->nPosStart != 0) {
		m_pLog->AddLine(_T("  ASSESSMENT not done as file offset non-zero"));
		if (bQuiet) { m_pLog->Enable(); }
		return false;
	}


	m_pLog->AddLine(_T("  Based on the analysis of compression characteristics and EXIF metadata:"));
	m_pLog->AddLine(_T(""));
	if (m_eImgEdited == EDITED_YES) {
		m_pLog->AddLine(_T("  ASSESSMENT: Class 1 - Image is processed/edited"));
	} else if (m_eImgEdited == EDITED_YESPROB) {
		m_pLog->AddLine(_T("  ASSESSMENT: Class 2 - Image has high probability of being processed/edited"));
	} else if (m_eImgEdited == EDITED_NO) {
		m_pLog->AddLine(_T("  ASSESSMENT: Class 3 - Image has high probability of being original"));

		if (bEditNotUnknownSw) {
			m_pLog->AddLine(_T("              Note that EXIF Software field is set (typically contains Firmware version)"));
		}
	} else if (m_eImgEdited == EDITED_UNSURE) {
		m_pLog->AddLine(_T("  ASSESSMENT: Class 4 - Uncertain if processed or original"));
		m_pLog->AddLine(_T("              While the EXIF fields indicate original, no compression signatures "));
		m_pLog->AddLine(_T("              in the current database were found matching this make/model"));
	} else {
		m_pLog->AddLineErr(_T("  ASSESSMENT: *** Failed to complete ***"));
	}
	m_pLog->AddLine(_T(""));


	bool bDbReqAdd = false;
	bool bDbReqAddAuto = false;


	m_eDbReqSuggest = DB_ADD_SUGGEST_UNSET;
	if (m_eImgEdited == EDITED_NO) {
		bDbReqAdd = false;
		m_eDbReqSuggest = DB_ADD_SUGGEST_CAM;
	} else if (m_eImgEdited == EDITED_UNSURE) {
		bDbReqAdd = true;
		bDbReqAddAuto = true;
		m_eDbReqSuggest = DB_ADD_SUGGEST_CAM;
		m_pLog->AddLine(_T("  Appears to be new signature for known camera."));
		m_pLog->AddLine(_T("  If the camera/software doesn't appear in list above,"));
		m_pLog->AddLineWarn(_T("  PLEASE ADD TO DATABASE with [Tools->Add Camera to DB]"));
	} else if (bCurXps && bSrchUsig) {

		bDbReqAdd = false;
		m_eDbReqSuggest = DB_ADD_SUGGEST_SW;
	} else if (bCurXps && !bSrchUsig) {

		bDbReqAdd = true;
		bDbReqAddAuto = true;
		m_eDbReqSuggest = DB_ADD_SUGGEST_SW;
		m_pLog->AddLine(_T("  Appears to be new signature for Photoshop."));
		m_pLog->AddLine(_T("  If it doesn't appear in list above,"));
		m_pLog->AddLineWarn(_T("  PLEASE ADD TO DATABASE with [Tools->Add Camera to DB]"));
	} else if (bCurXsw && bSrchXsw && bSrchXswUsig) {
		bDbReqAdd = false;
		m_eDbReqSuggest = DB_ADD_SUGGEST_SW;
	} else if (bCurXextrasw) {
		bDbReqAdd = false;
		m_eDbReqSuggest = DB_ADD_SUGGEST_SW;
	} else if (bCurXsw && bSrchXsw && !bSrchXswUsig) {
		bDbReqAdd = true;

		m_eDbReqSuggest = DB_ADD_SUGGEST_SW;
		m_pLog->AddLine(_T("  Appears to be new signature for known software."));
		m_pLog->AddLine(_T("  If the camera/software doesn't appear in list above,"));
		m_pLog->AddLineWarn(_T("  PLEASE ADD TO DATABASE with [Tools->Add Camera to DB]"));
	} else if (bCurXmm && bCurXmkr && !bSrchXsw && !bSrchXmmUsig) {

		bDbReqAdd = true;
		bDbReqAddAuto = true;
		m_eDbReqSuggest = DB_ADD_SUGGEST_CAM;
		m_pLog->AddLine(_T("  This may be a new camera for the database."));
		m_pLog->AddLine(_T("  If this file is original, and camera doesn't appear in list above,"));
		m_pLog->AddLineWarn(_T("  PLEASE ADD TO DATABASE with [Tools->Add Camera to DB]"));
	} else if (!bCurXmm && !bCurXmkr && !bSrchXsw) {

		bDbReqAdd = true;
		m_eDbReqSuggest = DB_ADD_SUGGEST_SW;
		m_pLog->AddLine(_T("  This may be a new software editor for the database."));
		m_pLog->AddLine(_T("  If this file is processed, and editor doesn't appear in list above,"));
		m_pLog->AddLineWarn(_T("  PLEASE ADD TO DATABASE with [Tools->Add Camera to DB]"));
	}


	m_pLog->AddLine(_T(""));


	if (bQuiet) { m_pLog->Enable(); }

#ifdef BATCH_DO_DBSUBMIT_ALL
	bDbReqAddAuto = true;
#endif


	return bDbReqAddAuto;

}
