SanitizeMsg(smsg_t *pMsg)
{
	DEFiRet;
	uchar *pszMsg;
	uchar *pDst;
	size_t lenMsg;
	size_t iSrc;
	size_t iDst;
	size_t iMaxLine;
	size_t maxDest;
	uchar pc;
	sbool bUpdatedLen = RSFALSE;
	uchar szSanBuf[32*1024];

	assert(pMsg != NULL);
	assert(pMsg->iLenRawMsg > 0);

	pszMsg = pMsg->pszRawMsg;
	lenMsg = pMsg->iLenRawMsg;


	if(pszMsg[lenMsg-1] == '\0') {
		DBGPRINTF("dropped NUL at very end of message\n");
		bUpdatedLen = RSTRUE;
		lenMsg--;
	}


	if(glbl.GetParserDropTrailingLFOnReception()
	   && lenMsg > 0 && pszMsg[lenMsg-1] == '\n') {
		DBGPRINTF("dropped LF at very end of message (DropTrailingLF is set)\n");
		lenMsg--;
		pszMsg[lenMsg] = '\0';
		bUpdatedLen = RSTRUE;
	}


	int bNeedSanitize = 0;
	for(iSrc = 0 ; iSrc < lenMsg ; iSrc++) {
		if(pszMsg[iSrc] < 32) {
			if(glbl.GetParserSpaceLFOnReceive() && pszMsg[iSrc] == '\n') {
				pszMsg[iSrc] = ' ';
			} else if(pszMsg[iSrc] == '\0' || glbl.GetParserEscapeControlCharactersOnReceive()) {
				bNeedSanitize = 1;
				if (!glbl.GetParserSpaceLFOnReceive()) {
					break;
			    }
			}
		} else if(pszMsg[iSrc] > 127 && glbl.GetParserEscape8BitCharactersOnReceive()) {
			bNeedSanitize = 1;
			break;
		}
	}

	if(!bNeedSanitize) {
		if(bUpdatedLen == RSTRUE)
			MsgSetRawMsgSize(pMsg, lenMsg);
		FINALIZE;
	}


	iMaxLine = glbl.GetMaxLine();
	maxDest = lenMsg * 4;

	if(maxDest > iMaxLine)
		maxDest = iMaxLine;
	if(maxDest < sizeof(szSanBuf))
		pDst = szSanBuf;
	else
		CHKmalloc(pDst = MALLOC(maxDest + 1));
	if(iSrc > 0) {
		iSrc--;
		if(iSrc > maxDest) {
			DBGPRINTF("parser.Sanitize: have oversize index %zd, "
				"max %zd - corrected, but should not happen\n",
				iSrc, maxDest);
			iSrc = maxDest;
		}
		memcpy(pDst, pszMsg, iSrc);
	}
	iDst = iSrc;
	while(iSrc < lenMsg && iDst < maxDest - 3) {
		if((pszMsg[iSrc] < 32) && (pszMsg[iSrc] != '\t' || glbl.GetParserEscapeControlCharacterTab())) {


			if(pszMsg[iSrc] == '\0' || glbl.GetParserEscapeControlCharactersOnReceive()) {


				if (glbl.GetParserEscapeControlCharactersCStyle()) {
					pDst[iDst++] = '\\';

					switch (pszMsg[iSrc]) {
					case '\0':
						pDst[iDst++] = '0';
						break;
					case '\a':
						pDst[iDst++] = 'a';
						break;
					case '\b':
						pDst[iDst++] = 'b';
						break;
					case '\e':
						pDst[iDst++] = 'e';
						break;
					case '\f':
						pDst[iDst++] = 'f';
						break;
					case '\n':
						pDst[iDst++] = 'n';
						break;
					case '\r':
						pDst[iDst++] = 'r';
						break;
					case '\t':
						pDst[iDst++] = 't';
						break;
					case '\v':
						pDst[iDst++] = 'v';
						break;
					default:
						pDst[iDst++] = 'x';

						pc = pszMsg[iSrc];
						pDst[iDst++] = hexdigit[(pc & 0xF0) >> 4];
						pDst[iDst++] = hexdigit[pc & 0xF];

						break;
					}

				} else {
					pDst[iDst++] = glbl.GetParserControlCharacterEscapePrefix();
					pDst[iDst++] = '0' + ((pszMsg[iSrc] & 0300) >> 6);
					pDst[iDst++] = '0' + ((pszMsg[iSrc] & 0070) >> 3);
					pDst[iDst++] = '0' + ((pszMsg[iSrc] & 0007));
				}
			}

		} else if(pszMsg[iSrc] > 127 && glbl.GetParserEscape8BitCharactersOnReceive()) {
			if (glbl.GetParserEscapeControlCharactersCStyle()) {
				pDst[iDst++] = '\\';
				pDst[iDst++] = 'x';

				pc = pszMsg[iSrc];
				pDst[iDst++] = hexdigit[(pc & 0xF0) >> 4];
				pDst[iDst++] = hexdigit[pc & 0xF];

			} else {


				pDst[iDst++] = glbl.GetParserControlCharacterEscapePrefix();
				pDst[iDst++] = '0' + ((pszMsg[iSrc] & 0300) >> 6);
				pDst[iDst++] = '0' + ((pszMsg[iSrc] & 0070) >> 3);
				pDst[iDst++] = '0' + ((pszMsg[iSrc] & 0007));
			}
		} else {
			pDst[iDst++] = pszMsg[iSrc];
		}
		++iSrc;
	}
	pDst[iDst] = '\0';

	MsgSetRawMsg(pMsg, (char*)pDst, iDst);

	if(pDst != szSanBuf)
		free(pDst);

finalize_it:
	RETiRet;
}
