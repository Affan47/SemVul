int parseRFCSyslogMsg(msg_t *pMsg, int flags)
{
	uchar *p2parse;
	uchar *pBuf;
	int lenMsg;
	int bContParse = 1;

	BEGINfunc
	assert(pMsg != NULL);
	assert(pMsg->pszRawMsg != NULL);
	p2parse = pMsg->pszRawMsg + pMsg->offAfterPRI;
	lenMsg = pMsg->iLenRawMsg - pMsg->offAfterPRI;


	assert(p2parse[0] == '1' && p2parse[1] == ' ');
	p2parse += 2;
	lenMsg -= 2;


	if((pBuf = malloc(sizeof(uchar) * (lenMsg + 1))) == NULL)
		return 1;


	if(datetime.ParseTIMESTAMP3339(&(pMsg->tTIMESTAMP),  &p2parse, &lenMsg) == RS_RET_OK) {
		if(flags & IGNDATE) {

			memcpy(&pMsg->tTIMESTAMP, &pMsg->tRcvdAt, sizeof(struct syslogTime));
		}
	} else {
		DBGPRINTF("no TIMESTAMP detected!\n");
		bContParse = 0;
	}


	if(bContParse) {
		parseRFCField(&p2parse, pBuf, &lenMsg);
		MsgSetHOSTNAME(pMsg, pBuf, ustrlen(pBuf));
	}


	if(bContParse) {
		parseRFCField(&p2parse, pBuf, &lenMsg);
		MsgSetAPPNAME(pMsg, (char*)pBuf);
	}


	if(bContParse) {
		parseRFCField(&p2parse, pBuf, &lenMsg);
		MsgSetPROCID(pMsg, (char*)pBuf);
	}


	if(bContParse) {
		parseRFCField(&p2parse, pBuf, &lenMsg);
		MsgSetMSGID(pMsg, (char*)pBuf);
	}


	if(bContParse) {
		parseRFCStructuredData(&p2parse, pBuf, &lenMsg);
		MsgSetStructuredData(pMsg, (char*)pBuf);
	}


	MsgSetMSGoffs(pMsg, p2parse - pMsg->pszRawMsg);

	free(pBuf);
	ENDfunc
	return 0;
}
