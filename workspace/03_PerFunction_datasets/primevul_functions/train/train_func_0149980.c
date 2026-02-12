static inline rsRetVal printline(uchar *hname, uchar *hnameIP, uchar *msg, int flags, flowControl_t flowCtlType,
	prop_t *pInputName, struct syslogTime *stTime, time_t ttGenTime)
{
	DEFiRet;
	register uchar *p;
	int pri;
	msg_t *pMsg;
	prop_t *propFromHost = NULL;
	prop_t *propFromHostIP = NULL;


	if(stTime == NULL) {
		CHKiRet(msgConstruct(&pMsg));
	} else {
		CHKiRet(msgConstructWithTime(&pMsg, stTime, ttGenTime));
	}
	if(pInputName != NULL)
		MsgSetInputName(pMsg, pInputName);
	MsgSetFlowControlType(pMsg, flowCtlType);
	MsgSetRawMsgWOSize(pMsg, (char*)msg);


	pri = DEFUPRI;
	p = msg;
	if (*p == '<') {
		pri = 0;
		while (isdigit((int) *++p))
		{
		   pri = 10 * pri + (*p - '0');
		}
		if (*p == '>')
			++p;
	}
	if (pri &~ (LOG_FACMASK|LOG_PRIMASK))
		pri = DEFUPRI;
	pMsg->iFacility = LOG_FAC(pri);
	pMsg->iSeverity = LOG_PRI(pri);


	if((pMsg->msgFlags & PARSE_HOSTNAME) == 0)
		MsgSetHOSTNAME(pMsg, hname, ustrlen(hname));
	MsgSetRcvFromStr(pMsg, hname, ustrlen(hname), &propFromHost);
	CHKiRet(MsgSetRcvFromIPStr(pMsg, hnameIP, ustrlen(hnameIP), &propFromHostIP));
	MsgSetAfterPRIOffs(pMsg, p - msg);
	prop.Destruct(&propFromHost);
	prop.Destruct(&propFromHostIP);

	logmsg(pMsg, flags);

finalize_it:
	RETiRet;
}
