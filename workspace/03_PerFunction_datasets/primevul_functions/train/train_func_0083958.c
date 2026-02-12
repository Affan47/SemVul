unsigned CjfifDecode::DecodeMarker()
{
	TCHAR			acIdentifier[MAX_IDENTIFIER];
	CString			strTmp;
	CString			strFull;
	unsigned		nLength;
	unsigned		nTmpVal;
	unsigned		nCode;
	unsigned long	nPosEnd;
	unsigned long	nPosSaved;
	unsigned long	nPosExifStart;
	unsigned		nRet;
	bool			bRet;
	unsigned long	nPosMarkerStart;

	unsigned		nColTransform = 0;


	CString	strDqtPrecision = _T("");
	CString	strDqtZigZagOrder = _T("");


	if (Buf(m_nPos) != 0xFF) {
		if (m_nPos == 0) {

			if ((!m_bAvi) && (!m_bPsd)) {
				strTmp.Format(_T("NOTE: File did not start with JPEG marker. Consider using [Tools->Img Search Fwd] to locate embedded JPEG."));
				m_pLog->AddLineErr(strTmp);
			}
		} else {
			strTmp.Format(_T("ERROR: Expected marker 0xFF, got 0x%02X @ offset 0x%08X. Consider using [Tools->Img Search Fwd/Rev]."),Buf(m_nPos),m_nPos);
			m_pLog->AddLineErr(strTmp);
		}
		m_nPos++;
		return DECMARK_ERR;
	}
	m_nPos++;


	nCode = Buf(m_nPos++);


	unsigned	nSkipMarkerPad = 0;
	while (nCode == 0xFF) {

		nSkipMarkerPad++;

		nCode = Buf(m_nPos++);
	}


	if (nSkipMarkerPad>0) {
		strTmp.Format(_T("*** Skipped %u marker pad bytes ***"),nSkipMarkerPad);
		m_pLog->AddLineHdr(strTmp);
	}


	nPosMarkerStart = m_nPos;

	AddHeader(nCode);

	switch (nCode)
	{
	case JFIF_SOI:
		m_bStateSoi = true;
		break;


	case JFIF_APP12:

		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);

		strTmp.Format(_T("  Length          = %u"),nLength);
		m_pLog->AddLine(strTmp);

		nPosSaved = m_nPos;

		m_nPos += 2;

		_tcscpy_s(acIdentifier,MAX_IDENTIFIER,m_pWBuf->BufReadStrn(m_nPos,MAX_IDENTIFIER-1));
		acIdentifier[MAX_IDENTIFIER-1] = 0;
		strTmp.Format(_T("  Identifier      = [%s]"),acIdentifier);
		m_pLog->AddLine(strTmp);
		m_nPos += (unsigned)_tcslen(acIdentifier)+1;
		if (_tcscmp(acIdentifier,_T("Ducky")) != 0)
		{
			m_pLog->AddLine(_T("    Not Photoshop DUCKY. Skipping remainder."));
		}
		else
		{


			m_nImgQualPhotoshopSfw = Buf(m_nPos+6);
			strTmp.Format(_T("  Photoshop Save For Web Quality = [%d]"),m_nImgQualPhotoshopSfw);
			m_pLog->AddLine(strTmp);
		}


		m_nPos = nPosSaved+nLength;
		break;

	case JFIF_APP14:


		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
		strTmp.Format(_T("  Length            = %u"),nLength);
		m_pLog->AddLine(strTmp);

		nPosSaved = m_nPos;

		if (nLength < 2+12) {
			m_pLog->AddLine(_T("    Segment too short for Identifier. Skipping remainder."));
			m_nPos = nPosSaved+nLength;
			break;
		}
		m_nPos += 2;


		m_nPos += 5;

		nTmpVal = Buf(m_nPos+0)*256 + Buf(m_nPos+1);
		strTmp.Format(_T("  DCTEncodeVersion  = %u"),nTmpVal);
		m_pLog->AddLine(strTmp);

		nTmpVal = Buf(m_nPos+2)*256 + Buf(m_nPos+3);
		strTmp.Format(_T("  APP14Flags0       = %u"),nTmpVal);
		m_pLog->AddLine(strTmp);

		nTmpVal = Buf(m_nPos+4)*256 + Buf(m_nPos+5);
		strTmp.Format(_T("  APP14Flags1       = %u"),nTmpVal);
		m_pLog->AddLine(strTmp);

		nColTransform = Buf(m_nPos+6);
		switch (nColTransform) {
		case APP14_COLXFM_UNK_RGB:
			strTmp.Format(_T("  ColorTransform    = %u [Unknown (RGB or CMYK)]"),nColTransform);
			break;
		case APP14_COLXFM_YCC:
			strTmp.Format(_T("  ColorTransform    = %u [YCbCr]"),nColTransform);
			break;
		case APP14_COLXFM_YCCK:
			strTmp.Format(_T("  ColorTransform    = %u [YCCK]"),nColTransform);
			break;
		default:
			strTmp.Format(_T("  ColorTransform    = %u [???]"),nColTransform);
			break;

		}
		m_pLog->AddLine(strTmp);
		m_nApp14ColTransform = (nColTransform & 0xFF);


		m_nPos = nPosSaved+nLength;

		break;

	case JFIF_APP13:

		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);

		strTmp.Format(_T("  Length          = %u"),nLength);
		m_pLog->AddLine(strTmp);

		nPosSaved = m_nPos;


		if (nLength < 2+20) {
			m_pLog->AddLine(_T("    Segment too short for Identifier. Skipping remainder."));
			m_nPos = nPosSaved+nLength;
			break;
		}
		m_nPos += 2;

		_tcscpy_s(acIdentifier,MAX_IDENTIFIER,m_pWBuf->BufReadStrn(m_nPos,MAX_IDENTIFIER-1));
		acIdentifier[MAX_IDENTIFIER-1] = 0;
		strTmp.Format(_T("  Identifier      = [%s]"),acIdentifier);
		m_pLog->AddLine(strTmp);
		m_nPos += (unsigned)_tcslen(acIdentifier)+1;
		if (_tcscmp(acIdentifier,_T("Photoshop 3.0")) != 0)
		{
			m_pLog->AddLine(_T("    Not Photoshop. Skipping remainder."));
		}
		else
		{
			DecodeApp13Ps();
		}


		m_nPos = nPosSaved+nLength;
		break;

	case JFIF_APP1:
		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);

		strTmp.Format(_T("  Length          = %u"),nLength);
		m_pLog->AddLine(strTmp);

		nPosSaved = m_nPos;

		m_nPos += 2;

		_tcscpy_s(acIdentifier,MAX_IDENTIFIER,m_pWBuf->BufReadStrn(m_nPos,MAX_IDENTIFIER-1));
		acIdentifier[MAX_IDENTIFIER-1] = 0;
		strTmp.Format(_T("  Identifier      = [%s]"),acIdentifier);
		m_pLog->AddLine(strTmp);
		m_nPos += (unsigned)_tcslen(acIdentifier);


		if (!_tcsnccmp(acIdentifier,_T("http://ns.adobe.com/xap/1.0/\x00"),29) != 0) {


			m_pLog->AddLine(_T("    XMP = "));

			m_nPos++;

			unsigned nPosMarkerEnd = nPosSaved+nLength-1;
			unsigned sXmpLen = nPosMarkerEnd-m_nPos;
			char cXmpChar;
			bool bNonSpace;
			CString strLine;


			strLine = _T("          |");
			bNonSpace = false;

			for (unsigned nInd=0;nInd<sXmpLen;nInd++) {


				cXmpChar = (char)m_pWBuf->Buf(m_nPos+nInd);


				if ((cXmpChar != 0x20) && (cXmpChar != 0x0A)) {
					bNonSpace = true;
				}


				if (cXmpChar == 0x0A) {

					if (bNonSpace) {
						m_pLog->AddLine(strLine);
					}

					strLine = _T("          |");
					bNonSpace = false;
				} else {

					strLine.AppendChar(cXmpChar);
				}
			}
		}
		else if (!_tcscmp(acIdentifier,_T("Exif")) != 0)
		{


			m_nPos += 2;


			nPosExifStart = m_nPos;


			unsigned char acIdentifierTiff[9];
			strFull = _T("");
			strTmp = _T("");

			strFull = _T("  Identifier TIFF = ");
			for (unsigned int i=0;i<8;i++) {
				acIdentifierTiff[i] = (unsigned char)Buf(m_nPos++);
			}
			strTmp = PrintAsHexUC(acIdentifierTiff,8);
			strFull += strTmp;
			m_pLog->AddLine(strFull);


			switch (acIdentifierTiff[0]*256+acIdentifierTiff[1])
			{
			case 0x4949:

				m_nImgExifEndian = 0;
				m_pLog->AddLine(_T("  Endian          = Intel (little)"));
				break;
			case 0x4D4D:

				m_nImgExifEndian = 1;
				m_pLog->AddLine(_T("  Endian          = Motorola (big)"));
				break;
			}


			unsigned test_002a;
			test_002a = ByteSwap2(acIdentifierTiff[2],acIdentifierTiff[3]);
			strTmp.Format(_T("  TAG Mark x002A  = 0x%04X"),test_002a);
			m_pLog->AddLine(strTmp);

			unsigned nIfdCount;
			unsigned nOffsetIfd1;


			m_nImgExifSubIfdPtr = 0;
			m_nImgExifMakerPtr = 0;
			m_nImgExifGpsIfdPtr = 0;
			m_nImgExifInteropIfdPtr = 0;

			bool exif_done = FALSE;

			nOffsetIfd1 = ByteSwap4(acIdentifierTiff[4],acIdentifierTiff[5],
				acIdentifierTiff[6],acIdentifierTiff[7]);


			if ((nPosSaved + nLength) <= (nPosExifStart+nOffsetIfd1)) {

				exif_done = true;
				m_pLog->AddLine(_T("  NOTE: No IFD entries"));
			}


			nIfdCount = 0;
			while (!exif_done) {

				m_pLog->AddLine(_T(""));

				strTmp.Format(_T("IFD%u"),nIfdCount);


				nRet = DecodeExifIfd(strTmp,nPosExifStart,nOffsetIfd1);


				nOffsetIfd1 = ByteSwap4(Buf(m_nPos+0),Buf(m_nPos+1),Buf(m_nPos+2),Buf(m_nPos+3));
				m_nPos += 4;


				strTmp.Format(_T("    Offset to Next IFD = 0x%08X"),nOffsetIfd1);
				m_pLog->AddLine(strTmp);


				if (nRet != 0) {

					nOffsetIfd1 = 0x00000000;
				}


				if (nOffsetIfd1 == 0x00000000) {

					exif_done = TRUE;
				} else {
					nIfdCount++;
				}

			}


			if (m_nImgExifSubIfdPtr != 0)
			{
				m_pLog->AddLine(_T(""));
				DecodeExifIfd(_T("SubIFD"),nPosExifStart,m_nImgExifSubIfdPtr);
			}
			if (m_nImgExifMakerPtr != 0)
			{
				m_pLog->AddLine(_T(""));
				DecodeExifIfd(_T("MakerIFD"),nPosExifStart,m_nImgExifMakerPtr);
			}
			if (m_nImgExifGpsIfdPtr != 0)
			{
				m_pLog->AddLine(_T(""));
				DecodeExifIfd(_T("GPSIFD"),nPosExifStart,m_nImgExifGpsIfdPtr);
			}
			if (m_nImgExifInteropIfdPtr != 0)
			{
				m_pLog->AddLine(_T(""));
				DecodeExifIfd(_T("InteropIFD"),nPosExifStart,m_nImgExifInteropIfdPtr);
			}

		} else {
			strTmp.Format(_T("Identifier [%s] not supported. Skipping remainder."),(LPCTSTR)acIdentifier);
			m_pLog->AddLine(strTmp);
		}


#if 0
		unsigned ptr_base;

		if (m_bVerbose)
		{
			if (m_nImgExifMakerPtr != 0)
			{

				ptr_base = nPosExifStart+m_nImgExifMakerPtr;

				m_pLog->AddLine(_T("Exif Maker IFD DUMP"));
				strFull.Format(_T("  MarkerOffset @ 0x%08X"),ptr_base);
				m_pLog->AddLine(strFull);
			}
		}
#endif


		m_nPos = nPosSaved;


		m_nPos = nPosSaved+nLength;

		break;

	case JFIF_APP2:


		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);

		strTmp.Format(_T("  Length          = %u"),nLength);
		m_pLog->AddLine(strTmp);

		nPosSaved = m_nPos;

		m_nPos += 2;


		_tcscpy_s(acIdentifier,MAX_IDENTIFIER,m_pWBuf->BufReadStrn(m_nPos,MAX_IDENTIFIER-1));
		acIdentifier[MAX_IDENTIFIER-1] = 0;
		strTmp.Format(_T("  Identifier      = [%s]"),acIdentifier);
		m_pLog->AddLine(strTmp);
		m_nPos += (unsigned)_tcslen(acIdentifier)+1;
		if (_tcscmp(acIdentifier,_T("FPXR")) == 0) {

			m_pLog->AddLine(_T("    FlashPix:"));
			DecodeApp2Flashpix();
		} else if (_tcscmp(acIdentifier,_T("ICC_PROFILE")) == 0) {

			m_pLog->AddLine(_T("    ICC Profile:"));
			DecodeApp2IccProfile(nLength);
		} else {
			m_pLog->AddLine(_T("    Not supported. Skipping remainder."));
		}


		m_nPos = nPosSaved+nLength;
		break;


	case JFIF_APP3:
	case JFIF_APP4:
	case JFIF_APP5:
	case JFIF_APP6:
	case JFIF_APP7:
	case JFIF_APP8:
	case JFIF_APP9:
	case JFIF_APP10:
	case JFIF_APP11:


	case JFIF_APP15:
		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);

		strTmp.Format(_T("  Length     = %u"),nLength);
		m_pLog->AddLine(strTmp);

		if (m_bVerbose)
		{

			strFull = _T("");
			for (unsigned int i=0;i<nLength;i++)
			{

				if ((i % 16) == 0) {
					strFull.Format(_T("  MarkerOffset [%04X]: "),i);
				} else if ((i % 8) == 0) {
					strFull += _T("  ");
				}
				nTmpVal = Buf(m_nPos+i);
				strTmp.Format(_T("%02X "),nTmpVal);
				strFull += strTmp;
				if ((i%16) == 15) {
					m_pLog->AddLine(strFull);
					strFull = _T("");
				}
			}
			m_pLog->AddLine(strFull);

			strFull = _T("");
			for (unsigned int i=0;i<nLength;i++)
			{

				if ((i % 32) == 0) {
					strFull.Format(_T("  MarkerOffset [%04X]: "),i);
				} else if ((i % 8) == 0) {
					strFull += _T(" ");
				}
				nTmpVal = Buf(m_nPos+i);
				if (_istprint(nTmpVal)) {
					strTmp.Format(_T("%c"),nTmpVal);
					strFull += strTmp;
				} else {
					strFull += _T(".");
				}
				if ((i%32)==31) {
					m_pLog->AddLine(strFull);
				}
			}
			m_pLog->AddLine(strFull);

		}

		m_nPos += nLength;
		break;

	case JFIF_APP0:

		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);

		m_nPos+=2;
		strTmp.Format(_T("  Length     = %u"),nLength);
		m_pLog->AddLine(strTmp);

		_tcscpy_s(m_acApp0Identifier,MAX_IDENTIFIER,m_pWBuf->BufReadStrn(m_nPos,MAX_IDENTIFIER-1));
		m_acApp0Identifier[MAX_IDENTIFIER-1] = 0;
		strTmp.Format(_T("  Identifier = [%s]"),m_acApp0Identifier);
		m_pLog->AddLine(strTmp);

		if (!_tcscmp(m_acApp0Identifier,_T("JFIF")))
		{


			m_nPos += (unsigned)(_tcslen(m_acApp0Identifier)+1);

			m_nImgVersionMajor = Buf(m_nPos++);
			m_nImgVersionMinor = Buf(m_nPos++);
			strTmp.Format(_T("  version    = [%u.%u]"),m_nImgVersionMajor,m_nImgVersionMinor);
			m_pLog->AddLine(strTmp);

			m_nImgUnits = Buf(m_nPos++);

			m_nImgDensityX = Buf(m_nPos)*256 + Buf(m_nPos+1);

			m_nPos+=2;
			m_nImgDensityY = Buf(m_nPos)*256 + Buf(m_nPos+1);

			m_nPos+=2;
			strTmp.Format(_T("  density    = %u x %u "),m_nImgDensityX,m_nImgDensityY);
			strFull = strTmp;

			switch (m_nImgUnits)
			{
			case 0:
				strFull += _T("(aspect ratio)");
				m_pLog->AddLine(strFull);
				break;
			case 1:
				strFull += _T("DPI (dots per inch)");
				m_pLog->AddLine(strFull);
				break;
			case 2:
				strFull += _T("DPcm (dots per cm)");
				m_pLog->AddLine(strFull);
				break;
			default:
				strTmp.Format(_T("ERROR: Unknown ImgUnits parameter [%u]"),m_nImgUnits);
				strFull += strTmp;
				m_pLog->AddLineWarn(strFull);

				break;
			}


			m_nImgThumbSizeX = Buf(m_nPos++);
			m_nImgThumbSizeY = Buf(m_nPos++);
			strTmp.Format(_T("  thumbnail  = %u x %u"),m_nImgThumbSizeX,m_nImgThumbSizeY);
			m_pLog->AddLine(strTmp);


			unsigned thumbnail_r,thumbnail_g,thumbnail_b;
			if (m_nImgThumbSizeX && m_nImgThumbSizeY) {
				for (unsigned y=0;y<m_nImgThumbSizeY;y++) {
					strFull.Format(_T("   Thumb[%03u] = "),y);
					for (unsigned x=0;x<m_nImgThumbSizeX;x++) {
						thumbnail_r = Buf(m_nPos++);
						thumbnail_g = Buf(m_nPos++);
						thumbnail_b = Buf(m_nPos++);
						strTmp.Format(_T("(0x%02X,0x%02X,0x%02X) "),thumbnail_r,thumbnail_g,thumbnail_b);
						strFull += strTmp;
						m_pLog->AddLine(strFull);
					}
				}
			}


		} else if (!_tcsnccmp(m_acApp0Identifier,_T("AVI1"),4))
		{


			m_pLog->AddLine(_T("  Detected MotionJPEG"));
			m_pLog->AddLine(_T("  Importing standard Huffman table..."));
			m_pLog->AddLine(_T(""));

			AddHeader(JFIF_DHT_FAKE);

			DecodeDHT(true);

			m_bStateDht = true;
			m_bStateDhtFake = true;
			m_bStateDhtOk = true;

			m_nPos += nLength-2;


		} else {

			m_pLog->AddLine(_T("    Not known APP0 type. Skipping remainder."));
			m_nPos += nLength-2;
		}

		if (!ExpectMarkerEnd(nPosMarkerStart,nLength))
			return DECMARK_ERR;

		break;

	case JFIF_DQT:
		m_bStateDqt = true;
		unsigned nDqtPrecision_Pq;
		unsigned nDqtQuantDestId_Tq;
		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
		nPosEnd = m_nPos+nLength;
		m_nPos+=2;

		strTmp.Format(_T("  Table length = %u"),nLength);
		m_pLog->AddLine(strTmp);

		while (nPosEnd > m_nPos)
		{
			strTmp.Format(_T("  ----"));
			m_pLog->AddLine(strTmp);

			nTmpVal = Buf(m_nPos++);
			nDqtPrecision_Pq = (nTmpVal & 0xF0) >> 4;
			nDqtQuantDestId_Tq = nTmpVal & 0x0F;


#if 1

			if (nDqtPrecision_Pq == 0) {
				strDqtPrecision = _T("8 bits");
			} else if (nDqtPrecision_Pq == 1) {
				strDqtPrecision = _T("16 bits");
			} else {
				strTmp.Format(_T("    Unsupported precision value [%u]"),nDqtPrecision_Pq);
				m_pLog->AddLineWarn(strTmp);
				strDqtPrecision = _T("???");

			}

			if (!ValidateValue(nDqtPrecision_Pq,0,1,_T("DQT Precision <Pq>"),true,0)) return DECMARK_ERR;
			if (!ValidateValue(nDqtQuantDestId_Tq,0,3,_T("DQT Destination ID <Tq>"),true,0)) return DECMARK_ERR;

			strTmp.Format(_T("  Precision=%s"),(LPCTSTR)strDqtPrecision);
			m_pLog->AddLine(strTmp);

#else


			if ((nDqtPrecision_Pq & 0xE) == 0) {

				if (nDqtPrecision_Pq == 0) {
					strDqtPrecision = _T("8 bits");
				} else if (nDqtPrecision_Pq == 1) {
					strDqtPrecision = _T("16 bits");
				}
				strTmp.Format(_T("  Precision=%s"),strDqtPrecision);
				m_pLog->AddLine(strTmp);
			} else {


				strTmp.Format(_T("  Non-Standard DQT Extension detected"));
				m_pLog->AddLineWarn(strTmp);


				if (nDqtPrecision_Pq == 0) {
					strDqtPrecision = _T("8 bits");
				} else if (nDqtPrecision_Pq == 1) {
					strDqtPrecision = _T("16 bits");
				}
				strTmp.Format(_T("  Precision=%s"),strDqtPrecision);
				m_pLog->AddLine(strTmp);

				if ((nDqtPrecision_Pq & 0x2) == 0) {
					strDqtZigZagOrder = _T("Diagonal zig-zag coeff scan seqeunce");
				} else if ((nDqtPrecision_Pq & 0x2) == 1) {
					strDqtZigZagOrder = _T("Alternate coeff scan seqeunce");
				}
				strTmp.Format(_T("  Coeff Scan Sequence=%s"),strDqtZigZagOrder);
				m_pLog->AddLine(strTmp);

				if ((nDqtPrecision_Pq & 0x4) == 1) {
					strTmp.Format(_T("  Custom coeff scan sequence"));
					m_pLog->AddLine(strTmp);

					CString strSequence = _T("");
					for (unsigned nInd=0;nInd<64;nInd++) {
						nTmpVal = Buf(m_nPos++);
						strTmp.Format(_T("%u"),nTmpVal);
						strSequence += strTmp;
						if (nInd!=63) {
							strSequence += _T(", ");
						}
					}
					strTmp.Format(_T("  Custom sequence = [ %s ]"),strSequence);
					m_pLog->AddLine(strTmp);
				}
			}
#endif

			strTmp.Format(_T("  Destination ID=%u"),nDqtQuantDestId_Tq);
			if (nDqtQuantDestId_Tq == 0) {
				strTmp += _T(" (Luminance)");
			}
			else if (nDqtQuantDestId_Tq == 1) {
				strTmp += _T(" (Chrominance)");
			}
			else if (nDqtQuantDestId_Tq == 2) {
				strTmp += _T(" (Chrominance)");
			}
			else {
				strTmp += _T(" (???)");
			}
			m_pLog->AddLine(strTmp);


			if (nDqtQuantDestId_Tq >= MAX_DQT_DEST_ID) {
				strTmp.Format(_T("ERROR: Destination ID <Tq> = %u, >= %u"),nDqtQuantDestId_Tq,MAX_DQT_DEST_ID);
				m_pLog->AddLineErr(strTmp);
				if (!m_pAppConfig->bRelaxedParsing) {
					m_pLog->AddLineErr(_T("  Stopping decode"));
					return DECMARK_ERR;
				} else {


					strTmp.Format(_T("  Skipping remainder of marker [%u bytes]"),nPosMarkerStart + nLength - m_nPos);
					m_pLog->AddLineWarn(strTmp);
					m_pLog->AddLine(_T(""));
					m_nPos = nPosMarkerStart + nLength;
					return DECMARK_OK;
				}
			}

			bool	bQuantAllOnes = true;
			double	dComparePercent;
			double	dSumPercent=0;
			double	dSumPercentSqr=0;


			for (unsigned nCoeffInd=0;nCoeffInd<MAX_DQT_COEFF;nCoeffInd++)
			{
				nTmpVal = Buf(m_nPos++);
				if (nDqtPrecision_Pq == 1) {

					nTmpVal <<= 8;
					nTmpVal += Buf(m_nPos++);
				}
				m_anImgDqtTbl[nDqtQuantDestId_Tq][glb_anZigZag[nCoeffInd]] = nTmpVal;


				if (nDqtQuantDestId_Tq == 0) {
					if (m_anImgDqtTbl[nDqtQuantDestId_Tq][glb_anZigZag[nCoeffInd]] != 0) {
						m_afStdQuantLumCompare[glb_anZigZag[nCoeffInd]] =
							(float)(glb_anStdQuantLum[glb_anZigZag[nCoeffInd]]) /
							(float)(m_anImgDqtTbl[nDqtQuantDestId_Tq][glb_anZigZag[nCoeffInd]]);
						dComparePercent = 100.0 *
							(double)(m_anImgDqtTbl[nDqtQuantDestId_Tq][glb_anZigZag[nCoeffInd]]) /
							(double)(glb_anStdQuantLum[glb_anZigZag[nCoeffInd]]);
					} else {
						m_afStdQuantLumCompare[glb_anZigZag[nCoeffInd]] = (float)999.99;
						dComparePercent = 999.99;
					}
				} else {
					if (m_anImgDqtTbl[nDqtQuantDestId_Tq][glb_anZigZag[nCoeffInd]] != 0) {
						m_afStdQuantChrCompare[glb_anZigZag[nCoeffInd]] =
							(float)(glb_anStdQuantChr[glb_anZigZag[nCoeffInd]]) /
							(float)(m_anImgDqtTbl[nDqtQuantDestId_Tq][glb_anZigZag[nCoeffInd]]);
						dComparePercent = 100.0 *
							(double)(m_anImgDqtTbl[nDqtQuantDestId_Tq][glb_anZigZag[nCoeffInd]]) /
							(double)(glb_anStdQuantChr[glb_anZigZag[nCoeffInd]]);

					} else {
						m_afStdQuantChrCompare[glb_anZigZag[nCoeffInd]] = (float)999.99;
					}
				}

				dSumPercent += dComparePercent;
				dSumPercentSqr += dComparePercent * dComparePercent;


				if (m_anImgDqtTbl[nDqtQuantDestId_Tq][glb_anZigZag[nCoeffInd]] != 1) bQuantAllOnes = 0;


			}


			m_abImgDqtSet[nDqtQuantDestId_Tq] = true;

			unsigned nCoeffInd;


			for (unsigned nDqtY=0;nDqtY<8;nDqtY++) {
				strFull.Format(_T("    DQT, Row #%u: "),nDqtY);
				for (unsigned nDqtX=0;nDqtX<8;nDqtX++) {
					nCoeffInd = nDqtY*8+nDqtX;
					strTmp.Format(_T("%3u "),m_anImgDqtTbl[nDqtQuantDestId_Tq][nCoeffInd]);
					strFull += strTmp;


					bRet = m_pImgDec->SetDqtEntry(nDqtQuantDestId_Tq,nCoeffInd,glb_anUnZigZag[nCoeffInd],
						m_anImgDqtTbl[nDqtQuantDestId_Tq][nCoeffInd]);
					DecodeErrCheck(bRet);
				}


				m_pLog->AddLine(strFull);

			}


			double	dQuality;
			double	dVariance;
			dSumPercent /= 64.0;
			dSumPercentSqr /= 64.0;
			dVariance = dSumPercentSqr - (dSumPercent * dSumPercent);


			if (bQuantAllOnes)
				dQuality = 100.0;
			else if (dSumPercent <= 100.0)
				dQuality = (200.0 - dSumPercent) / 2.0;
			else
				dQuality = 5000.0 / dSumPercent;


			m_adImgDqtQual[nDqtQuantDestId_Tq] = dQuality;

			strTmp.Format(_T("    Approx quality factor = %.2f (scaling=%.2f variance=%.2f)"),
				dQuality,dSumPercent,dVariance);
			m_pLog->AddLine(strTmp);


		}
		m_bStateDqtOk = true;

		if (!ExpectMarkerEnd(nPosMarkerStart,nLength))
			return DECMARK_ERR;

		break;

	case JFIF_DAC:
		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
		m_nPos+=2;

		strTmp.Format(_T("  Arithmetic coding header length = %u"),nLength);
		m_pLog->AddLine(strTmp);
		unsigned	nDAC_n;
		unsigned	nDAC_Tc,nDAC_Tb;
		unsigned	nDAC_Cs;
		nDAC_n = (nLength>2)?(nLength-2)/2:0;
		for (unsigned nInd=0;nInd<nDAC_n;nInd++) {
			nTmpVal = Buf(m_nPos++);
			nDAC_Tc = (nTmpVal & 0xF0) >> 4;
			nDAC_Tb = (nTmpVal & 0x0F);

			strTmp.Format(_T("  #%02u: Table class                  = %u"),nInd+1,nDAC_Tc);
			m_pLog->AddLine(strTmp);

			strTmp.Format(_T("  #%02u: Table destination identifier = %u"),nInd+1,nDAC_Tb);
			m_pLog->AddLine(strTmp);

			nDAC_Cs = Buf(m_nPos++);

			strTmp.Format(_T("  #%02u: Conditioning table value     = %u"),nInd+1,nDAC_Cs);
			m_pLog->AddLine(strTmp);

			if (!ValidateValue(nDAC_Tc,0,1,_T("Table class <Tc>"),true,0)) return DECMARK_ERR;
			if (!ValidateValue(nDAC_Tb,0,3,_T("Table destination ID <Tb>"),true,0)) return DECMARK_ERR;


			if (!ValidateValue(nDAC_Cs,0,255,_T("Conditioning table value <Cs>"),true,0)) return DECMARK_ERR;
		}
		if (!ExpectMarkerEnd(nPosMarkerStart,nLength))
			return DECMARK_ERR;

		break;

	case JFIF_DNL:
		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
		m_nPos+=2;

		strTmp.Format(_T("  Header length = %u"),nLength);
		m_pLog->AddLine(strTmp);

		nTmpVal = Buf(m_nPos)*256 + Buf(m_nPos+1);
		m_nPos+=2;

		strTmp.Format(_T("  Number of lines = %u"),nTmpVal);
		m_pLog->AddLine(strTmp);

		if (!ValidateValue(nTmpVal,1,65535,_T("Number of lines <NL>"),true,1)) return DECMARK_ERR;

		if (!ExpectMarkerEnd(nPosMarkerStart,nLength))
			return DECMARK_ERR;
		break;

	case JFIF_EXP:
		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
		m_nPos+=2;

		strTmp.Format(_T("  Header length = %u"),nLength);
		m_pLog->AddLine(strTmp);

		unsigned	nEXP_Eh,nEXP_Ev;
		nTmpVal = Buf(m_nPos)*256 + Buf(m_nPos+1);
		nEXP_Eh = (nTmpVal & 0xF0) >> 4;
		nEXP_Ev = (nTmpVal & 0x0F);
		m_nPos+=2;

		strTmp.Format(_T("  Expand horizontally = %u"),nEXP_Eh);
		m_pLog->AddLine(strTmp);

		strTmp.Format(_T("  Expand vertically   = %u"),nEXP_Ev);
		m_pLog->AddLine(strTmp);

		if (!ValidateValue(nEXP_Eh,0,1,_T("Expand horizontally <Eh>"),true,0)) return DECMARK_ERR;
		if (!ValidateValue(nEXP_Ev,0,1,_T("Expand vertically <Ev>"),true,0)) return DECMARK_ERR;

		if (!ExpectMarkerEnd(nPosMarkerStart,nLength))
			return DECMARK_ERR;
		break;


	case JFIF_SOF0:
	case JFIF_SOF1:
	case JFIF_SOF2:
	case JFIF_SOF3:
	case JFIF_SOF5:
	case JFIF_SOF6:
	case JFIF_SOF7:
	case JFIF_SOF9:
	case JFIF_SOF10:
	case JFIF_SOF11:
	case JFIF_SOF13:
	case JFIF_SOF14:
	case JFIF_SOF15:


		m_bStateSof = true;


		m_bImgSofUnsupported = true;
		if (nCode == JFIF_SOF0) { m_bImgSofUnsupported = false; }
		if (nCode == JFIF_SOF1) { m_bImgSofUnsupported = false; }


		if (nCode == JFIF_SOF2) { m_bImgProgressive = true; }


		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
		m_nPos+=2;

		strTmp.Format(_T("  Frame header length = %u"),nLength);
		m_pLog->AddLine(strTmp);

		m_nSofPrecision_P = Buf(m_nPos++);

		strTmp.Format(_T("  Precision = %u"),m_nSofPrecision_P);
		m_pLog->AddLine(strTmp);
		if (!ValidateValue(m_nSofPrecision_P,2,16,_T("Precision <P>"),true,8)) return DECMARK_ERR;

		m_nSofNumLines_Y = Buf(m_nPos)*256 + Buf(m_nPos+1);
		m_nPos += 2;

		strTmp.Format(_T("  Number of Lines = %u"),m_nSofNumLines_Y);
		m_pLog->AddLine(strTmp);
		if (!ValidateValue(m_nSofNumLines_Y,0,65535,_T("Number of Lines <Y>"),true,0)) return DECMARK_ERR;

		m_nSofSampsPerLine_X = Buf(m_nPos)*256 + Buf(m_nPos+1);
		m_nPos += 2;

		strTmp.Format(_T("  Samples per Line = %u"),m_nSofSampsPerLine_X);
		m_pLog->AddLine(strTmp);
		if (!ValidateValue(m_nSofSampsPerLine_X,1,65535,_T("Samples per Line <X>"),true,1)) return DECMARK_ERR;

		strTmp.Format(_T("  Image Size = %u x %u"),m_nSofSampsPerLine_X,m_nSofNumLines_Y);
		m_pLog->AddLine(strTmp);


		m_eImgLandscape = ENUM_LANDSCAPE_YES;
		if (m_nSofNumLines_Y > m_nSofSampsPerLine_X)
			m_eImgLandscape = ENUM_LANDSCAPE_NO;
		strTmp.Format(_T("  Raw Image Orientation = %s"),(m_eImgLandscape==ENUM_LANDSCAPE_YES)?_T("Landscape"):_T("Portrait"));
		m_pLog->AddLine(strTmp);

		m_nSofNumComps_Nf = Buf(m_nPos++);

		strTmp.Format(_T("  Number of Img components = %u"),m_nSofNumComps_Nf);
		m_pLog->AddLine(strTmp);
		if (!ValidateValue(m_nSofNumComps_Nf,1,255,_T("Number of Img components <Nf>"),true,1)) return DECMARK_ERR;

		unsigned nCompIdent;
		unsigned anSofSampFact[MAX_SOF_COMP_NF];

		m_nSofHorzSampFactMax_Hmax = 0;
		m_nSofVertSampFactMax_Vmax = 0;


		for (unsigned nCompInd=1;((!m_bStateAbort)&&(nCompInd<=m_nSofNumComps_Nf));nCompInd++)
		{
			nCompIdent = Buf(m_nPos++);
			m_anSofQuantCompId[nCompInd] = nCompIdent;


			anSofSampFact[nCompIdent] = Buf(m_nPos++);
			m_anSofQuantTblSel_Tqi[nCompIdent] = Buf(m_nPos++);


			m_anSofHorzSampFact_Hi[nCompIdent] = (anSofSampFact[nCompIdent] & 0xF0) >> 4;
			m_anSofVertSampFact_Vi[nCompIdent] = (anSofSampFact[nCompIdent] & 0x0F);


		}


		for (unsigned nCompInd=1;((!m_bStateAbort)&&(nCompInd<=m_nSofNumComps_Nf));nCompInd++)
		{
			nCompIdent = m_anSofQuantCompId[nCompInd];


			m_nSofHorzSampFactMax_Hmax = max(m_nSofHorzSampFactMax_Hmax,m_anSofHorzSampFact_Hi[nCompIdent]);
			m_nSofVertSampFactMax_Vmax = max(m_nSofVertSampFactMax_Vmax,m_anSofVertSampFact_Vi[nCompIdent]);
		}


		for (unsigned nCompInd=1;((!m_bStateAbort)&&(nCompInd<=m_nSofNumComps_Nf));nCompInd++)
		{
			nCompIdent = m_anSofQuantCompId[nCompInd];


			CString		strSubsampH = _T("?");
			CString		strSubsampV = _T("?");
			if (m_anSofHorzSampFact_Hi[nCompIdent] > 0) {
				strSubsampH.Format(_T("%u"),m_nSofHorzSampFactMax_Hmax/m_anSofHorzSampFact_Hi[nCompIdent]);
			}
			if (m_anSofVertSampFact_Vi[nCompIdent] > 0) {
				strSubsampV.Format(_T("%u"),m_nSofVertSampFactMax_Vmax/m_anSofVertSampFact_Vi[nCompIdent]);
			}

			strFull.Format(_T("    Component[%u]: "),nCompInd);

			strTmp.Format(_T("ID=0x%02X, Samp Fac=0x%02X (Subsamp %s x %s), Quant Tbl Sel=0x%02X"),
				nCompIdent,anSofSampFact[nCompIdent],
				(LPCTSTR)strSubsampH,(LPCTSTR)strSubsampV,
				m_anSofQuantTblSel_Tqi[nCompIdent]);
			strFull += strTmp;


			if (m_nSofNumComps_Nf == 1) {

				strFull += _T(" (Lum: Y)");
			} else if (m_nSofNumComps_Nf == 3) {

				if (nCompInd == SCAN_COMP_Y) {
					strFull += _T(" (Lum: Y)");
				}
				else if (nCompInd == SCAN_COMP_CB) {
					strFull += _T(" (Chrom: Cb)");
				}
				else if (nCompInd == SCAN_COMP_CR) {
					strFull += _T(" (Chrom: Cr)");
				}
			} else if (m_nSofNumComps_Nf == 4) {

				if (nCompInd == 1) {
					strFull += _T(" (Y)");
				}
				else if (nCompInd == 2) {
					strFull += _T(" (Cb)");
				}
				else if (nCompInd == 3) {
					strFull += _T(" (Cr)");
				}
				else if (nCompInd == 4) {
					strFull += _T(" (K)");
				}
			} else {
				strFull += _T(" (???)");
			}
			m_pLog->AddLine(strFull);

		}


		for (unsigned nCompInd=1;((!m_bStateAbort)&&(nCompInd<=m_nSofNumComps_Nf));nCompInd++)
		{
			nCompIdent = m_anSofQuantCompId[nCompInd];
			if (!ValidateValue(m_anSofQuantCompId[nCompInd],0,255,_T("Component ID <Ci>"),true,0)) return DECMARK_ERR;
			if (!ValidateValue(m_anSofQuantTblSel_Tqi[nCompIdent],0,3,_T("Table Destination ID <Tqi>"),true,0)) return DECMARK_ERR;
			if (!ValidateValue(m_anSofHorzSampFact_Hi[nCompIdent],1,4,_T("Horizontal Sampling Factor <Hi>"),true,1)) return DECMARK_ERR;
			if (!ValidateValue(m_anSofVertSampFact_Vi[nCompIdent],1,4,_T("Vertical Sampling Factor <Vi>"),true,1)) return DECMARK_ERR;
		}


		for (unsigned nCompInd=1;((!m_bStateAbort)&&(nCompInd<=m_nSofNumComps_Nf));nCompInd++)
		{
			nCompIdent = m_anSofQuantCompId[nCompInd];


			bRet = m_pImgDec->SetDqtTables(nCompInd,m_anSofQuantTblSel_Tqi[nCompIdent]);
			DecodeErrCheck(bRet);


			m_pImgDec->SetPrecision(m_nSofPrecision_P);

		}

		if (!m_bStateAbort) {


			for (unsigned nCompInd=1;nCompInd<=m_nSofNumComps_Nf;nCompInd++) {


				nCompIdent = m_anSofQuantCompId[nCompInd];
				m_pImgDec->SetSofSampFactors(nCompInd,m_anSofHorzSampFact_Hi[nCompIdent],m_anSofVertSampFact_Vi[nCompIdent]);
			}


			m_bImgOK = true;

			m_bStateSofOk = true;

		}

		if (!ExpectMarkerEnd(nPosMarkerStart,nLength))
			return DECMARK_ERR;

		break;


	case JFIF_COM:
		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
		m_nPos+=2;
		strTmp.Format(_T("  Comment length = %u"),nLength);
		m_pLog->AddLine(strTmp);


		if ( (nLength == 0) || (nLength == 1) ) {
			strTmp.Format(_T("    JPEG Comment Field Vulnerability detected!"));
			m_pLog->AddLineErr(strTmp);
			strTmp.Format(_T("    Skipping data until next marker..."));
			m_pLog->AddLineErr(strTmp);
			nLength = 2;

			bool bDoneSearch = false;
			unsigned nSkipStart = m_nPos;
			while (!bDoneSearch) {
                if (Buf(m_nPos) != 0xFF) {
					m_nPos++;
				} else {
					bDoneSearch = true;
				}
				if (m_nPos >= m_pWBuf->GetPosEof()) {
					bDoneSearch = true;
				}
			}
			strTmp.Format(_T("    Skipped %u bytes"),m_nPos - nSkipStart);
			m_pLog->AddLineErr(strTmp);


			break;
		}


		strFull = _T("    Comment=");
		m_strComment = _T("");
		for (unsigned ind=0;ind<nLength-2;ind++)
		{
			nTmpVal = Buf(m_nPos++);
			if (_istprint(nTmpVal)) {
				strTmp.Format(_T("%c"),nTmpVal);
				m_strComment += strTmp;
			} else {
				m_strComment += _T(".");
			}
		}
		strFull += m_strComment;
		m_pLog->AddLine(strFull);

		break;

	case JFIF_DHT:
		m_bStateDht = true;
		DecodeDHT(false);
		m_bStateDhtOk = true;
		break;

	case JFIF_SOS:
		unsigned long nPosScanStart;

		m_bStateSos = true;


		if (m_nPosSos == 0) {
			m_nPosSos = m_nPos-2;
		}

		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
		m_nPos+=2;


		if (!m_bStateSofOk) {
			strTmp.Format(_T("  ERROR: SOS before valid SOF defined"));
			m_pLog->AddLineErr(strTmp);
			return DECMARK_ERR;
		}

		strTmp.Format(_T("  Scan header length = %u"),nLength);
		m_pLog->AddLine(strTmp);

		m_nSosNumCompScan_Ns = Buf(m_nPos++);

		strTmp.Format(_T("  Number of img components = %u"),m_nSosNumCompScan_Ns);
		m_pLog->AddLine(strTmp);


		if (m_nSosNumCompScan_Ns > MAX_SOS_COMP_NS) {
			strTmp.Format(_T("  ERROR: Scan decode does not support > %u components"),MAX_SOS_COMP_NS);
			m_pLog->AddLineErr(strTmp);
			return DECMARK_ERR;
		}

		unsigned nSosCompSel_Cs;
		unsigned nSosHuffTblSel;
		unsigned nSosHuffTblSelDc_Td;
		unsigned nSosHuffTblSelAc_Ta;

		for (unsigned int nScanCompInd=1;((nScanCompInd<=m_nSosNumCompScan_Ns) && (!m_bStateAbort));nScanCompInd++)
		{
			strFull.Format(_T("    Component[%u]: "),nScanCompInd);
			nSosCompSel_Cs = Buf(m_nPos++);
			nSosHuffTblSel = Buf(m_nPos++);
			nSosHuffTblSelDc_Td = (nSosHuffTblSel & 0xf0)>>4;
			nSosHuffTblSelAc_Ta = (nSosHuffTblSel & 0x0f);
			strTmp.Format(_T("selector=0x%02X, table=%u(DC),%u(AC)"),nSosCompSel_Cs,nSosHuffTblSelDc_Td,nSosHuffTblSelAc_Ta);
			strFull += strTmp;
			m_pLog->AddLine(strFull);

			bRet = m_pImgDec->SetDhtTables(nScanCompInd,nSosHuffTblSelDc_Td,nSosHuffTblSelAc_Ta);

			DecodeErrCheck(bRet);
		}


		m_nSosSpectralStart_Ss = Buf(m_nPos++);
		m_nSosSpectralEnd_Se = Buf(m_nPos++);
		m_nSosSuccApprox_A = Buf(m_nPos++);

		strTmp.Format(_T("  Spectral selection = %u .. %u"),m_nSosSpectralStart_Ss,m_nSosSpectralEnd_Se);
		m_pLog->AddLine(strTmp);
		strTmp.Format(_T("  Successive approximation = 0x%02X"),m_nSosSuccApprox_A);
		m_pLog->AddLine(strTmp);

		if (m_pAppConfig->bOutputScanDump) {
			m_pLog->AddLine(_T(""));
			m_pLog->AddLine(_T("  Scan Data: (after bitstuff removed)"));
		}


		nPosScanStart = m_nPos;


			bool		bSkipDone;
			unsigned	nSkipCount;
			unsigned	nSkipData;
			unsigned	nSkipPos;
			bool		bScanDumpTrunc;

			bSkipDone = false;
			nSkipCount = 0;
			nSkipPos = 0;
			bScanDumpTrunc = FALSE;

			strFull = _T("");
			while (!bSkipDone)
			{
				nSkipCount++;
				nSkipPos++;
				nSkipData = Buf(m_nPos++);

				if (nSkipData == 0xFF) {

					nSkipData = Buf(m_nPos++);
					nSkipCount++;
					if (nSkipData == 0x00) {

						nSkipData = 0xFF;
					} else if ((nSkipData >= JFIF_RST0) && (nSkipData <= JFIF_RST7)) {

					} else {

						bSkipDone = true;
						m_nPos -= 2;
					}
				}

				if (m_pAppConfig->bOutputScanDump && (!bSkipDone) ) {

					if (nSkipPos > 640) {
						if (!bScanDumpTrunc) {
							m_pLog->AddLineWarn(_T("    WARNING: Dump truncated."));
							bScanDumpTrunc = TRUE;
						}
					} else {
						if ( ((nSkipPos-1) == 0) || (((nSkipPos-1) % 32) == 0) ) {
							strFull = _T("    ");
						}

						strTmp.Format(_T("%02x "),nSkipData);
						strFull += strTmp;

						if (((nSkipPos-1) % 32) == 31) {
							m_pLog->AddLine(strFull);
							strFull = _T("");
						}
					}
				}


				if (!m_pWBuf->GetBufOk()) {
					strTmp.Format(_T("ERROR: Ran out of buffer before EOI during phase 1 of Scan decode @ 0x%08X"),m_nPos);
					m_pLog->AddLineErr(strTmp);
					break;
				}

			}
			m_pLog->AddLine(strFull);


		if (m_pAppConfig->bDecodeScanImg && m_bImgSofUnsupported) {

			m_pLog->AddLineWarn(_T("  NOTE: Scan parsing doesn't support this SOF mode."));
#ifndef DEBUG_YCCK
		} else if (m_pAppConfig->bDecodeScanImg && (m_nSofNumComps_Nf == 4)) {
			m_pLog->AddLineWarn(_T("  NOTE: Scan parsing doesn't support CMYK files yet."));
#endif
		} else if (m_pAppConfig->bDecodeScanImg && !m_bImgSofUnsupported) {
			if (!m_bStateSofOk) {
				m_pLog->AddLineWarn(_T("  NOTE: Scan decode disabled as SOF not decoded."));
			} else if (!m_bStateDqtOk) {
				m_pLog->AddLineWarn(_T("  NOTE: Scan decode disabled as DQT not decoded."));
			} else if (!m_bStateDhtOk) {
				m_pLog->AddLineWarn(_T("  NOTE: Scan decode disabled as DHT not decoded."));

			} else {
				m_pLog->AddLine(_T(""));


				m_pImgDec->SetImageDetails(m_nSofSampsPerLine_X,m_nSofNumLines_Y,
					m_nSofNumComps_Nf,m_nSosNumCompScan_Ns,m_nImgRstEn,m_nImgRstInterval);


				if (m_pImgSrcDirty) {
					m_pImgDec->DecodeScanImg(nPosScanStart,true,false);
					m_pImgSrcDirty = false;
				}
			}

		}

		m_bStateSosOk = true;

		break;

	case JFIF_DRI:
		unsigned	nVal;
		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
		strTmp.Format(_T("  Length     = %u"),nLength);
		m_pLog->AddLine(strTmp);
		nVal = Buf(m_nPos+2)*256 + Buf(m_nPos+3);


		m_nImgRstInterval = nVal;
		if (nVal != 0) {
			m_nImgRstEn = true;
		} else {
			m_nImgRstEn = false;
		}
		strTmp.Format(_T("  interval   = %u"),m_nImgRstInterval);
		m_pLog->AddLine(strTmp);
		m_nPos += 4;
		if (!ExpectMarkerEnd(nPosMarkerStart,nLength))
			return DECMARK_ERR;
		break;

	case JFIF_EOI:
		m_pLog->AddLine(_T(""));


		m_nPosEmbedEnd = m_nPos;
		m_nPosEoi = m_nPos;
		m_bStateEoi = true;

		return DECMARK_EOI;

		break;


	case JFIF_DHP:

	case JFIF_JPG:
	case JFIF_JPG0:
	case JFIF_JPG1:
	case JFIF_JPG2:
	case JFIF_JPG3:
	case JFIF_JPG4:
	case JFIF_JPG5:
	case JFIF_JPG6:
	case JFIF_JPG7:
	case JFIF_JPG8:
	case JFIF_JPG9:
	case JFIF_JPG10:
	case JFIF_JPG11:
	case JFIF_JPG12:
	case JFIF_JPG13:
	case JFIF_TEM:


		nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
		strTmp.Format(_T("  Header length = %u"),nLength);
		m_pLog->AddLine(strTmp);
		m_pLog->AddLineWarn(_T("  Skipping unsupported marker"));
		m_nPos += nLength;
		break;

	case JFIF_RST0:
	case JFIF_RST1:
	case JFIF_RST2:
	case JFIF_RST3:
	case JFIF_RST4:
	case JFIF_RST5:
	case JFIF_RST6:
	case JFIF_RST7:


		strTmp.Format(_T("  WARNING: Restart marker [0xFF%02X] detected outside scan"),nCode);
		m_pLog->AddLineWarn(strTmp);
		if (!m_pAppConfig->bRelaxedParsing) {

			m_pLog->AddLineErr(_T("  Stopping decode"));
			m_pLog->AddLine(_T("  Use [Img Search Fwd/Rev] to locate other valid embedded JPEGs"));
			return DECMARK_ERR;
		} else {


			if (Buf(m_nPos+2) == 0xFF) {

				m_pLog->AddLineWarn(_T("  Ignoring standalone marker. Proceeding with decode."));
				m_nPos += 2;
			} else {


				nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
				strTmp.Format(_T("  Header length = %u"),nLength);
				m_pLog->AddLine(strTmp);
				m_pLog->AddLineWarn(_T("  Skipping marker"));
				m_nPos += nLength;
			}
		}
		break;

	default:
		strTmp.Format(_T("  WARNING: Unknown marker [0xFF%02X]"),nCode);
		m_pLog->AddLineWarn(strTmp);
		if (!m_pAppConfig->bRelaxedParsing) {

			m_pLog->AddLineErr(_T("  Stopping decode"));
			m_pLog->AddLine(_T("  Use [Img Search Fwd/Rev] to locate other valid embedded JPEGs"));
			return DECMARK_ERR;
		} else {

			nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
			strTmp.Format(_T("  Header length = %u"),nLength);
			m_pLog->AddLine(strTmp);
			m_pLog->AddLineWarn(_T("  Skipping marker"));
			m_nPos += nLength;
		}
	}


	m_pLog->AddLine(_T(" "));


	if (m_bStateAbort) {
		return DECMARK_ERR;
	}

	return DECMARK_OK;
}
