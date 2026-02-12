relpTcpConnectTLSInit(relpTcp_t *pThis)
{
	int r;
	int sockflags;
	ENTER_RELPFUNC;
	RELPOBJ_assert(pThis, Tcp);


	if((sockflags = fcntl(pThis->sock, F_GETFL)) != -1) {
		sockflags &= ~O_NONBLOCK;
		sockflags = fcntl(pThis->sock, F_SETFL, sockflags);
	}

	if(sockflags == -1) {
		pThis->pEngine->dbgprint("error %d unsetting fcntl(O_NONBLOCK) on relp socket", errno);
		ABORT_FINALIZE(RELP_RET_IO_ERR);
	}

	if(!called_gnutls_global_init) {
		#if GNUTLS_VERSION_NUMBER <= 0x020b00

		gcry_control (GCRYCTL_SET_THREAD_CBS, &gcry_threads_pthread);
		#endif
		gnutls_global_init();


		pThis->pEngine->dbgprint("DDDD: gnutls_global_init() called\n");
		called_gnutls_global_init = 1;
	}
	r = gnutls_init(&pThis->session, GNUTLS_CLIENT);
	if(chkGnutlsCode(pThis, "Failed to initialize GnuTLS", RELP_RET_ERR_TLS_SETUP, r)) {
		ABORT_FINALIZE(RELP_RET_ERR_TLS_SETUP);
	}

	gnutls_session_set_ptr(pThis->session, pThis);
	CHKRet(relpTcpTLSSetPrio(pThis));

	if(isAnonAuth(pThis)) {
		r = gnutls_anon_allocate_client_credentials(&pThis->anoncred);
		if(chkGnutlsCode(pThis, "Failed to allocate client credentials", RELP_RET_ERR_TLS_SETUP, r)) {
			ABORT_FINALIZE(RELP_RET_ERR_TLS_SETUP);
		}

		r = gnutls_credentials_set(pThis->session, GNUTLS_CRD_ANON, pThis->anoncred);
		if(chkGnutlsCode(pThis, "Failed to set credentials", RELP_RET_ERR_TLS_SETUP, r)) {
			ABORT_FINALIZE(RELP_RET_ERR_TLS_SETUP);
		}
	} else {
#ifdef HAVE_GNUTLS_CERTIFICATE_SET_VERIFY_FUNCTION
		r = gnutls_certificate_allocate_credentials(&pThis->xcred);
		if(chkGnutlsCode(pThis, "Failed to allocate certificate credentials", RELP_RET_ERR_TLS_SETUP, r)) {
			ABORT_FINALIZE(RELP_RET_ERR_TLS_SETUP);
		}
		if(pThis->caCertFile != NULL) {
			r = gnutls_certificate_set_x509_trust_file(pThis->xcred,
				pThis->caCertFile, GNUTLS_X509_FMT_PEM);
			if(r < 0) {
				chkGnutlsCode(pThis, "Failed to set certificate trust file", RELP_RET_ERR_TLS_SETUP, r);
				ABORT_FINALIZE(RELP_RET_ERR_TLS_SETUP);
			}
			pThis->pEngine->dbgprint("librelp: obtained %d certificates from %s\n", r, pThis->caCertFile);
		}
		if(pThis->ownCertFile != NULL) {
			r = gnutls_certificate_set_x509_key_file (pThis->xcred,
				pThis->ownCertFile, pThis->privKeyFile, GNUTLS_X509_FMT_PEM);
			if(chkGnutlsCode(pThis, "Failed to set certificate key file", RELP_RET_ERR_TLS_SETUP, r)) {
				ABORT_FINALIZE(RELP_RET_ERR_TLS_SETUP);
			}
		}
		r = gnutls_credentials_set(pThis->session, GNUTLS_CRD_CERTIFICATE, pThis->xcred);
		if(chkGnutlsCode(pThis, "Failed to set credentials", RELP_RET_ERR_TLS_SETUP, r)) {
			ABORT_FINALIZE(RELP_RET_ERR_TLS_SETUP);
		}
		if(pThis->authmode == eRelpAuthMode_None)
			pThis->authmode = eRelpAuthMode_Fingerprint;
		gnutls_certificate_set_verify_function(pThis->xcred, relpTcpVerifyCertificateCallback);
#		else
		ABORT_FINALIZE(RELP_RET_ERR_NO_TLS_AUTH);
#		endif
	}

	gnutls_transport_set_ptr(pThis->session, (gnutls_transport_ptr_t) pThis->sock);


	do {
		r = gnutls_handshake(pThis->session);
		pThis->pEngine->dbgprint("DDDD: gnutls_handshake: %d: %s\n", r, gnutls_strerror(r));
		if(r == GNUTLS_E_INTERRUPTED || r == GNUTLS_E_AGAIN) {
			pThis->pEngine->dbgprint("librelp: gnutls_handshake must be retried\n");
			pThis->rtryOp = relpTCP_RETRY_handshake;
		} else if(r != GNUTLS_E_SUCCESS) {
			chkGnutlsCode(pThis, "TLS handshake failed", RELP_RET_ERR_TLS_SETUP, r);
			ABORT_FINALIZE(RELP_RET_ERR_TLS_SETUP);
		}
	}
	while(0);


	if((sockflags = fcntl(pThis->sock, F_GETFL)) != -1) {
		sockflags |= O_NONBLOCK;


		sockflags = fcntl(pThis->sock, F_SETFL, sockflags);
	}
finalize_it:
	LEAVE_RELPFUNC;
}
