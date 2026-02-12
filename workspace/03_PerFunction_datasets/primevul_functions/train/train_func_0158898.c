void MsgSetRawMsg(msg_t *pThis, char* pszRawMsg, size_t lenMsg)
{
	assert(pThis != NULL);
	if(pThis->pszRawMsg != pThis->szRawMsg)
		free(pThis->pszRawMsg);

	pThis->iLenRawMsg = lenMsg;
	if(pThis->iLenRawMsg < CONF_RAWMSG_BUFSIZE) {

		pThis->pszRawMsg = pThis->szRawMsg;
	} else if((pThis->pszRawMsg = (uchar*) MALLOC(pThis->iLenRawMsg + 1)) == NULL) {

		pThis->pszRawMsg = pThis->szRawMsg;
		pThis->iLenRawMsg = CONF_RAWMSG_BUFSIZE - 1;
	}

	memcpy(pThis->pszRawMsg, pszRawMsg, pThis->iLenRawMsg);
	pThis->pszRawMsg[pThis->iLenRawMsg] = '\0';
}
