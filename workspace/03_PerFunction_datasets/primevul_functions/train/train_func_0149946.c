logmsg(msg_t *pMsg, int flags)
{
	char *msg;

	BEGINfunc
	assert(pMsg != NULL);
	assert(pMsg->pszRawMsg != NULL);

	msg = (char*) pMsg->pszRawMsg + pMsg->offAfterPRI;
	DBGPRINTF("logmsg: flags %x, from '%s', msg %s\n", flags, getRcvFrom(pMsg), msg);


	if(msg[0] == '1' && msg[1] == ' ') {
		DBGPRINTF("Message has syslog-protocol format.\n");
		setProtocolVersion(pMsg, 1);
		if(parseRFCSyslogMsg(pMsg, flags) == 1) {
			msgDestruct(&pMsg);
			return;
		}
	} else {
		DBGPRINTF("Message has legacy syslog format.\n");
		setProtocolVersion(pMsg, 0);
		if(parseLegacySyslogMsg(pMsg, flags) == 1) {
			msgDestruct(&pMsg);
			return;
		}
	}


	pMsg->msgFlags = flags;
	MsgPrepareEnqueue(pMsg);
	qqueueEnqObj(pMsgQueue, pMsg->flowCtlType, (void*) pMsg);
	ENDfunc
}
