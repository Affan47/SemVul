static rsRetVal addListner(void __attribute__((unused)) *pVal, uchar *pNewVal)
{
	DEFiRet;
	uchar *bindAddr;
	int *newSocks;
	int *tmpSocks;
	int iSrc, iDst;


	if(pszBindAddr == NULL)
		bindAddr = NULL;
	else if(pszBindAddr[0] == '*' && pszBindAddr[1] == '\0')
		bindAddr = NULL;
	else
		bindAddr = pszBindAddr;

	dbgprintf("Trying to open syslog UDP ports at %s:%s.\n",
		  (bindAddr == NULL) ? (uchar*)"*" : bindAddr, pNewVal);

	newSocks = net.create_udp_socket(bindAddr, (pNewVal == NULL || *pNewVal == '\0') ? (uchar*) "514" : pNewVal, 1);
	if(newSocks != NULL) {

		if(udpLstnSocks == NULL) {

			udpLstnSocks = newSocks;
		} else {

			if((tmpSocks = malloc(sizeof(int) * 1 + newSocks[0] + udpLstnSocks[0])) == NULL) {
				dbgprintf("out of memory trying to allocate udp listen socket array\n");


				free(newSocks);
				ABORT_FINALIZE(RS_RET_OUT_OF_MEMORY);
			} else {

				iDst = 1;
				for(iSrc = 1 ; iSrc <= udpLstnSocks[0] ; ++iSrc)
					tmpSocks[iDst++] = udpLstnSocks[iSrc];
				for(iSrc = 1 ; iSrc <= newSocks[0] ; ++iSrc)
					tmpSocks[iDst++] = newSocks[iSrc];
				tmpSocks[0] = udpLstnSocks[0] + newSocks[0];
				free(newSocks);
				free(udpLstnSocks);
				udpLstnSocks = tmpSocks;
			}
		}
	}

finalize_it:
	free(pNewVal);

	RETiRet;
}
