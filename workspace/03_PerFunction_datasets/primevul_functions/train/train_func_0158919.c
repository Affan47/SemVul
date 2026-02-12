static rsRetVal aquirePROCIDFromTAG(msg_t *pM)
{
	register int i;
	uchar *pszTag;
	DEFiRet;

	assert(pM != NULL);

	if(pM->pCSPROCID != NULL)
		return RS_RET_OK;

	if(getProtocolVersion(pM) != 0)
		return RS_RET_OK;

	pszTag = (uchar*) ((pM->iLenTAG < CONF_TAG_BUFSIZE) ? pM->TAG.szBuf : pM->TAG.pszTAG);


	i = 0;
	while((i < pM->iLenTAG) && (pszTag[i] != '['))
		++i;
	if(!(i < pM->iLenTAG))
		return RS_RET_OK;

	++i;


	CHKiRet(cstrConstruct(&pM->pCSPROCID));
	while((i < pM->iLenTAG) && (pszTag[i] != ']')) {
		CHKiRet(cstrAppendChar(pM->pCSPROCID, pszTag[i]));
		++i;
	}

	if(!(i < pM->iLenTAG)) {


		cstrDestruct(&pM->pCSPROCID);
		FINALIZE;
	}


	CHKiRet(cstrFinalize(pM->pCSPROCID));

finalize_it:
	RETiRet;
}
