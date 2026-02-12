rsRetVal MsgSetMSGID(msg_t *pMsg, char* pszMSGID)
{
	DEFiRet;
	ISOBJ_TYPE_assert(pMsg, msg);
	if(pMsg->pCSMSGID == NULL) {

		CHKiRet(rsCStrConstruct(&pMsg->pCSMSGID));
	}

	iRet = rsCStrSetSzStr(pMsg->pCSMSGID, (uchar*) pszMSGID);

finalize_it:
	RETiRet;
}
