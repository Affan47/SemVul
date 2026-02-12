void CjfifDecode::DecodeDHT(bool bInject)
{
	unsigned	nLength;
	unsigned	nTmpVal;
	CString		strTmp,strFull;
	unsigned	nPosEnd;
	unsigned	nPosSaved;

	bool		bRet;


	if (bInject) {


		m_bBufFakeDHT = true;


		nPosSaved = m_nPos;
		m_nPos = 2;
	}

	nLength = Buf(m_nPos)*256 + Buf(m_nPos+1);
	nPosEnd = m_nPos+nLength;
	m_nPos+=2;
	strTmp.Format(_T("  Huffman table length = %u"),nLength);
	m_pLog->AddLine(strTmp);

	unsigned	nDhtClass_Tc;
	unsigned	nDhtHuffTblId_Th;


	while ((!m_bStateAbort)&&(nPosEnd > m_nPos))
	{
		m_pLog->AddLine(_T("  ----"));

		nTmpVal = Buf(m_nPos++);
		nDhtClass_Tc = (nTmpVal & 0xF0) >> 4;
		nDhtHuffTblId_Th = nTmpVal & 0x0F;
		strTmp.Format(_T("  Destination ID = %u"),nDhtHuffTblId_Th);
		m_pLog->AddLine(strTmp);
		strTmp.Format(_T("  Class = %u (%s)"),nDhtClass_Tc,(nDhtClass_Tc?_T("AC Table"):_T("DC / Lossless Table")));
		m_pLog->AddLine(strTmp);


		if (nDhtClass_Tc >= MAX_DHT_CLASS) {
			strTmp.Format(_T("ERROR: Invalid DHT Class (%u). Aborting DHT Load."),nDhtClass_Tc);
			m_pLog->AddLineErr(strTmp);
			m_nPos = nPosEnd;

			break;
		}
		if (nDhtHuffTblId_Th >= MAX_DHT_DEST_ID) {
			strTmp.Format(_T("ERROR: Invalid DHT Dest ID (%u). Aborting DHT Load."),nDhtHuffTblId_Th);
			m_pLog->AddLineErr(strTmp);
			m_nPos = nPosEnd;

			break;
		}


		for (unsigned int i=1;i<=MAX_DHT_CODELEN;i++)
		{
			m_anDhtNumCodesLen_Li[i] = Buf(m_nPos++);
		}

		#define DECODE_DHT_MAX_DHT 256

		unsigned int	anDhtCodeVal[DECODE_DHT_MAX_DHT+1];
		unsigned int	nDhtInd;
		unsigned int	nDhtCodesTotal;


		for (nDhtInd = 0;nDhtInd <DECODE_DHT_MAX_DHT;nDhtInd++)
		{
			anDhtCodeVal[nDhtInd] = 0xFFFF;
		}


		nDhtCodesTotal = 0;
		nDhtInd = 0;
		for (unsigned int nIndLen=1;((!m_bStateAbort)&&(nIndLen<=MAX_DHT_CODELEN));nIndLen++)
		{

			nDhtCodesTotal += m_anDhtNumCodesLen_Li[nIndLen];

			strFull.Format(_T("    Codes of length %02u bits (%03u total): "),nIndLen,m_anDhtNumCodesLen_Li[nIndLen]);
			for (unsigned int nIndCode=0;((!m_bStateAbort)&&(nIndCode<m_anDhtNumCodesLen_Li[nIndLen]));nIndCode++)
			{

				if ( (nIndCode != 0) && ((nIndCode % 16) == 0) ) {
					strFull = _T("                                         ");
				}
				nTmpVal = Buf(m_nPos++);
				strTmp.Format(_T("%02X "),nTmpVal);
				strFull += strTmp;


				if ((nIndCode % 16) == 15) {
					m_pLog->AddLine(strFull);
					strFull = _T("");
				}


				if (nDhtInd < DECODE_DHT_MAX_DHT) {
					anDhtCodeVal[nDhtInd++] = nTmpVal;
				} else {
					nDhtInd++;
					strTmp.Format(_T("Excessive DHT entries (%u)... skipping"),nDhtInd);
					m_pLog->AddLineErr(strTmp);
					if (!m_bStateAbort) { DecodeErrCheck(true); }
				}

			}
			m_pLog->AddLine(strFull);
		}
		strTmp.Format(_T("    Total number of codes: %03u"),nDhtCodesTotal);
		m_pLog->AddLine(strTmp);

		unsigned int nDhtLookupInd = 0;


		unsigned long	nBitVal = 0;
		unsigned int	nCodeVal = 0;
		nDhtInd = 0;
		if (m_pAppConfig->bOutputDHTexpand) {
			m_pLog->AddLine(_T(""));
			m_pLog->AddLine(_T("  Expanded Form of Codes:"));
		}
		for (unsigned int nBitLen=1;((!m_bStateAbort)&&(nBitLen<=16));nBitLen++)
		{
			if (m_anDhtNumCodesLen_Li[nBitLen] > 0)
			{
				if (m_pAppConfig->bOutputDHTexpand) {
					strTmp.Format(_T("    Codes of length %02u bits:"),nBitLen);
					m_pLog->AddLine(strTmp);
				}


				for (unsigned int bit_ind=1;((!m_bStateAbort)&&(bit_ind<=m_anDhtNumCodesLen_Li[nBitLen]));bit_ind++)
				{
					unsigned int	nDecVal = nCodeVal;
					unsigned int	nBinBit;
					TCHAR			acBinStr[17] = _T("");
					unsigned int	nBinStrLen = 0;


					if (m_pAppConfig->bOutputDHTexpand) {
						for (unsigned int nBinInd=nBitLen;nBinInd>=1;nBinInd--)
						{
							nBinBit = (nDecVal >> (nBinInd-1)) & 1;
							acBinStr[nBinStrLen++] = (nBinBit)?'1':'0';
						}
						acBinStr[nBinStrLen] = '\0';
						strFull.Format(_T("      %s = %02X"),acBinStr,anDhtCodeVal[nDhtInd]);


						if (nDhtClass_Tc == DHT_CLASS_AC) {
							if (anDhtCodeVal[nDhtInd] == 0x00) { strFull += _T(" (EOB)"); }
							if (anDhtCodeVal[nDhtInd] == 0xF0) { strFull += _T(" (ZRL)"); }
						}

						strTmp.Format(_T("%-40s (Total Len = %2u)"),(LPCTSTR)strFull,nBitLen + (anDhtCodeVal[nDhtInd] & 0xF));

						m_pLog->AddLine(strTmp);
					}


					unsigned nTmpMask = m_anMaskLookup[nBitLen];

					unsigned nTmpBits = nDecVal << (32-nBitLen);
					unsigned nTmpCode = anDhtCodeVal[nDhtInd];
					bRet = m_pImgDec->SetDhtEntry(nDhtHuffTblId_Th,nDhtClass_Tc,nDhtLookupInd,nBitLen,
						nTmpBits,nTmpMask,nTmpCode);

					DecodeErrCheck(bRet);

					nDhtLookupInd++;


					nCodeVal++;
					nDhtInd++;
				}
			}

			nCodeVal <<= 1;
		}


		unsigned nTmpSize = nDhtLookupInd;
		bRet = m_pImgDec->SetDhtSize(nDhtHuffTblId_Th,nDhtClass_Tc,nTmpSize);
		if (!m_bStateAbort) { DecodeErrCheck(bRet); }

		m_pLog->AddLine(_T(""));

	}

	if (bInject) {

		m_nPos = nPosSaved;
		m_bBufFakeDHT = false;
	}
}
