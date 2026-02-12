AcceptConnReq(ptcplstn_t *pLstn, int *newSock, prop_t **peerName, prop_t **peerIP)
{
	int sockflags;
	struct sockaddr_storage addr;
	socklen_t addrlen = sizeof(addr);
	int iNewSock = -1;

	DEFiRet;

	iNewSock = accept(pLstn->sock, (struct sockaddr*) &addr, &addrlen);
	if(iNewSock < 0) {
		if(errno == EAGAIN || errno == EWOULDBLOCK || errno == EMFILE)
			ABORT_FINALIZE(RS_RET_NO_MORE_DATA);
		ABORT_FINALIZE(RS_RET_ACCEPT_ERR);
	}

	if(pLstn->pSrv->bKeepAlive)
		EnableKeepAlive(pLstn, iNewSock);

	CHKiRet(getPeerNames(peerName, peerIP, (struct sockaddr *) &addr, pLstn->pSrv->bUnixSocket));


	if((sockflags = fcntl(iNewSock, F_GETFL)) != -1) {
		sockflags |= O_NONBLOCK;


		sockflags = fcntl(iNewSock, F_SETFL, sockflags);
	}
	if(sockflags == -1) {
		DBGPRINTF("error %d setting fcntl(O_NONBLOCK) on tcp socket %d", errno, iNewSock);
		prop.Destruct(peerName);
		prop.Destruct(peerIP);
		ABORT_FINALIZE(RS_RET_IO_ERROR);
	}

	*newSock = iNewSock;

finalize_it:
	if(iRet != RS_RET_OK) {

		if(iNewSock != -1)
			close(iNewSock);
	}

	RETiRet;
}
