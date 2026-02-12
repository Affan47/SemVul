startupSrv(ptcpsrv_t *pSrv)
{
	DEFiRet;
	int error, maxs, on = 1;
	int sock = -1;
	int numSocks;
	int sockflags;
	struct addrinfo hints, *res = NULL, *r;
	uchar *lstnIP;
	int isIPv6 = 0;

	if (pSrv->bUnixSocket) {
		return startupUXSrv(pSrv);
	}

	lstnIP = pSrv->lstnIP == NULL ? UCHAR_CONSTANT("") : pSrv->lstnIP;

	DBGPRINTF("imptcp: creating listen socket on server '%s', port %s\n", lstnIP, pSrv->port);

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = glbl.GetDefPFFamily();
	hints.ai_socktype = SOCK_STREAM;

	error = getaddrinfo((char*)pSrv->lstnIP, (char*) pSrv->port, &hints, &res);
	if(error) {
		DBGPRINTF("error %d querying server '%s', port '%s'\n", error, pSrv->lstnIP, pSrv->port);
		ABORT_FINALIZE(RS_RET_INVALID_PORT);
	}


	for(maxs = 0, r = res; r != NULL ; r = r->ai_next, maxs++) {
		;
	}

	numSocks = 0;
	for(r = res; r != NULL ; r = r->ai_next) {
		sock = socket(r->ai_family, r->ai_socktype, r->ai_protocol);
		if(sock < 0) {
			if(!(r->ai_family == PF_INET6 && errno == EAFNOSUPPORT)) {
				DBGPRINTF("error %d creating tcp listen socket", errno);


				continue;
			}
		}

		if(r->ai_family == AF_INET6) {
			isIPv6 = 1;
#ifdef IPV6_V6ONLY
			int iOn = 1;
			if(setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&iOn, sizeof (iOn)) < 0) {
				close(sock);
				sock = -1;
				continue;
			}
#endif
		} else {
			isIPv6 = 0;
		}

		if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on)) < 0 ) {
			DBGPRINTF("error %d setting tcp socket option\n", errno);
			close(sock);
			sock = -1;
			continue;
		}


		if((sockflags = fcntl(sock, F_GETFL)) != -1) {
			sockflags |= O_NONBLOCK;


			sockflags = fcntl(sock, F_SETFL, sockflags);
		}
		if(sockflags == -1) {
			DBGPRINTF("error %d setting fcntl(O_NONBLOCK) on tcp socket", errno);
            close(sock);
			sock = -1;
			continue;
		}


#if !defined (_AIX)
#ifndef BSD
		if(net.should_use_so_bsdcompat()) {
			if (setsockopt(sock, SOL_SOCKET, SO_BSDCOMPAT,
					(char *) &on, sizeof(on)) < 0) {
				errmsg.LogError(errno, NO_ERRCODE, "TCP setsockopt(BSDCOMPAT)");
                                close(sock);
				sock = -1;
				continue;
			}
		}
#endif
#endif
		if( (bind(sock, r->ai_addr, r->ai_addrlen) < 0)
#ifndef IPV6_V6ONLY
		     && (errno != EADDRINUSE)
#endif
	    ) {

			char errStr[1024];
			rs_strerror_r(errno, errStr, sizeof(errStr));
			dbgprintf("error %d while binding tcp socket: %s\n", errno, errStr);
			close(sock);
			sock = -1;
			continue;
		}

		if(listen(sock, 511) < 0) {
			DBGPRINTF("tcp listen error %d, suspending\n", errno);
			close(sock);
			sock = -1;
			continue;
		}


		CHKiRet(addLstn(pSrv, sock, isIPv6));
		++numSocks;
	}

	if(numSocks != maxs) {
		DBGPRINTF("We could initialize %d TCP listen sockets out of %d we received "
		 	  "- this may or may not be an error indication.\n", numSocks, maxs);
	}

	if(numSocks == 0) {
		DBGPRINTF("No TCP listen sockets could successfully be initialized");
		ABORT_FINALIZE(RS_RET_COULD_NOT_BIND);
	}

finalize_it:
	if(res != NULL) {
		freeaddrinfo(res);
	}

	if(iRet != RS_RET_OK) {
		if(sock != -1) {
			close(sock);
		}
	}

	RETiRet;
}
