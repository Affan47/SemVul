rsRetVal MsgSetPROCID(msg_t *pMsg, char* pszPROCID)
{
	DEFiRet;
	ISOBJ_TYPE_assert(pMsg, msg);
	if(pMsg->pCSPROCID == NULL) {

		CHKiRet(cstrConstruct(&pMsg->pCSPROCID));
	}

	CHKiRet(rsCStrSetSzStr(pMsg->pCSPROCID, (uchar*) pszPROCID));
	CHKiRet(cstrFinalize(pMsg->pCSPROCID));

finalize_it:
	RETiRet;
}
