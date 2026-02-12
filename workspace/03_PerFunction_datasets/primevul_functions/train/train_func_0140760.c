relpTcpChkOnePeerWildcard(tcpPermittedPeerWildcardComp_t *pRoot, char *peername, int *pbFoundPositiveMatch)
{
	tcpPermittedPeerWildcardComp_t *pWildcard;
	char *pC;
	char *pStart;
	int iWildcard, iName;

	*pbFoundPositiveMatch = 0;
	pWildcard = pRoot;
	pC = peername;
	while(*pC != '\0') {
		if(pWildcard == NULL) {

			goto done;
		}
		pStart = pC;
		while(*pC != '\0' && *pC != '.') {
			++pC;
		}


		switch(pWildcard->wildcardType) {
			case tcpPEER_WILDCARD_NONE:
				if(   pWildcard->lenDomainPart != pC - pStart
				   || strncmp((char*)pStart, (char*)pWildcard->pszDomainPart, pC - pStart)) {
					goto done;
				}
				break;
			case tcpPEER_WILDCARD_AT_START:

				if(pWildcard->lenDomainPart > pC - pStart) {
					goto done;
				}
				iName = (size_t) (pC - pStart) - pWildcard->lenDomainPart;
				iWildcard = 0;
				while(iWildcard < pWildcard->lenDomainPart) {
					if(pWildcard->pszDomainPart[iWildcard] != pStart[iName]) {
						goto done;
					}
					++iName;
					++iWildcard;
				}
				break;
			case tcpPEER_WILDCARD_AT_END:
				if(   pWildcard->lenDomainPart > pC - pStart
				   || strncmp((char*)pStart, (char*)pWildcard->pszDomainPart,
					pWildcard->lenDomainPart)) {
					goto done;
				}
				break;
			case tcpPEER_WILDCARD_MATCH_ALL:

				break;
			case tcpPEER_WILDCARD_EMPTY_COMPONENT:
				if(pC - pStart > 0) {

					goto done;
				}
				break;
		}
		pWildcard =  pWildcard->pNext;


		if(*pC == '.')
			++pC;
	}


	if(pWildcard != NULL && pWildcard->wildcardType == tcpPEER_WILDCARD_EMPTY_COMPONENT)
		pWildcard = pWildcard->pNext;

	if(pWildcard != NULL) {


		goto done;
	}
	*pbFoundPositiveMatch = 1;
done:	return;
}
