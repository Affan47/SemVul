parseAndSubmitMessage(uchar *hname, uchar *hnameIP, uchar *msg, int len, int flags, flowControl_t flowCtlType,
	prop_t *pInputName, struct syslogTime *stTime, time_t ttGenTime)
{
	DEFiRet;
	register int iMsg;
	uchar *pMsg;
	uchar *pData;
	uchar *pEnd;
	int iMaxLine;
	uchar *tmpline = NULL;
#	ifdef USE_NETZIP
	uchar *deflateBuf = NULL;
	uLongf iLenDefBuf;
#	endif

	assert(hname != NULL);
	assert(hnameIP != NULL);
	assert(msg != NULL);
	assert(len >= 0);


	iMaxLine = glbl.GetMaxLine();
	CHKmalloc(tmpline = malloc(sizeof(uchar) * (iMaxLine + 1)));


	if(*(msg + len - 1) == '\0') {
		DBGPRINTF("dropped NUL at very end of message\n");
		len--;
	}


	if(bDropTrailingLF && *(msg + len - 1) == '\n') {
		DBGPRINTF("dropped LF at very end of message (DropTrailingLF is set)\n");
		len--;
	}

	iMsg = 0;
	pMsg = tmpline;
	pData = msg;
	pEnd = msg + len;

#	ifdef USE_NETZIP


	if(len > 0 && *msg == 'z') {


		int ret;
		iLenDefBuf = iMaxLine;
		CHKmalloc(deflateBuf = malloc(sizeof(uchar) * (iMaxLine + 1)));
		ret = uncompress((uchar *) deflateBuf, &iLenDefBuf, (uchar *) msg+1, len-1);
		DBGPRINTF("Compressed message uncompressed with status %d, length: new %ld, old %d.\n",
		        ret, (long) iLenDefBuf, len-1);


		if(ret != Z_OK) {
			errmsg.LogError(0, NO_ERRCODE, "Uncompression of a message failed with return code %d "
			            "- enable debug logging if you need further information. "
				    "Message ignored.", ret);
			FINALIZE;
		}
		pData = deflateBuf;
		pEnd = deflateBuf + iLenDefBuf;
	}
#	else


	if(len > 0 && *msg == 'z') {
		errmsg.LogError(0, NO_ERRCODE, "Received a compressed message, but rsyslogd does not have compression "
		         "support enabled. The message will be ignored.");
		FINALIZE;
	}
#	endif

	while(pData < pEnd) {
		if(iMsg >= iMaxLine) {


			if(iMsg == iMaxLine) {
				*(pMsg + iMsg) = '\0';
				printline(hname, hnameIP, tmpline, flags, flowCtlType, pInputName, stTime, ttGenTime);
			} else {


				DBGPRINTF("internal error: iMsg > max msg size in parseAndSubmitMessage()\n");
			}
			FINALIZE;
		}
		if(*pData == '\0') {


			if(iMsg + 3 < iMaxLine) {
				*(pMsg + iMsg++) =  cCCEscapeChar;
				*(pMsg + iMsg++) = '0';
				*(pMsg + iMsg++) = '0';
				*(pMsg + iMsg++) = '0';
			}


			++pData;
		} else if(bEscapeCCOnRcv && iscntrl((int) *pData)) {


			if(iMsg + 3 < iMaxLine) {
				*(pMsg + iMsg++) = cCCEscapeChar;
				*(pMsg + iMsg++) = '0' + ((*pData & 0300) >> 6);
				*(pMsg + iMsg++) = '0' + ((*pData & 0070) >> 3);
				*(pMsg + iMsg++) = '0' + ((*pData & 0007));
			}
			++pData;
		} else {
			*(pMsg + iMsg++) = *pData++;
		}
	}

	*(pMsg + iMsg) = '\0';


	printline(hname, hnameIP, tmpline, flags, flowCtlType, pInputName, stTime, ttGenTime);

finalize_it:
	if(tmpline != NULL)
		free(tmpline);
#	ifdef USE_NETZIP
	if(deflateBuf != NULL)
		free(deflateBuf);
#	endif
	RETiRet;
}
