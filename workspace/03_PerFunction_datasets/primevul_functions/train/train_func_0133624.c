ParsePRI(smsg_t *pMsg)
{
	syslog_pri_t pri;
	uchar *msg;
	int lenMsg;
	DEFiRet;


	lenMsg = pMsg->iLenRawMsg;
	msg = pMsg->pszRawMsg;
	pri = DEFUPRI;
	if(pMsg->msgFlags & NO_PRI_IN_RAW) {

		MsgSetAfterPRIOffs(pMsg, 0);
	} else {
		if(*msg == '<') {
			pri = 0;
			while(--lenMsg > 0 && isdigit((int) *++msg) && pri <= LOG_MAXPRI) {
				pri = 10 * pri + (*msg - '0');
			}
			if(*msg == '>') {
				++msg;
			} else {
				pri = LOG_PRI_INVLD;
			}
			if(pri > LOG_MAXPRI)
				pri = LOG_PRI_INVLD;
		}
		msgSetPRI(pMsg, pri);
		MsgSetAfterPRIOffs(pMsg, (pri == LOG_PRI_INVLD) ? 0 : msg - pMsg->pszRawMsg);
	}
	RETiRet;
}
