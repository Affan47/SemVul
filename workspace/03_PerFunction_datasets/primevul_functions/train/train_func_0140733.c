relpTcpPermittedPeerWildcardCompile(tcpPermittedPeerEntry_t *pEtry)
{
	char *pC;
	char *pStart;
	ENTER_RELPFUNC;


	for(pC = pEtry->name ; *pC != '\0' && *pC != '*' ; ++pC)
		;

	if(*pC == '\0') {
		FINALIZE;
	}


	pC = pEtry->name;
	while(*pC) {
		pStart = pC;

		for( ; *pC != '\0' && *pC != '.' ; ++pC)
			;
		CHKRet(AddPermittedPeerWildcard(pEtry, pStart, pC - pStart));

		if(*pC == '.' && *(pC + 1) == '\0') {

			CHKRet(AddPermittedPeerWildcard(pEtry, pStart, 0));
		}
		if(*pC != '\0')
			++pC;
	}

finalize_it:
	LEAVE_RELPFUNC;
}
