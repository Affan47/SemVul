static int eaptls_initiate(void *type_arg, EAP_HANDLER *handler)
{
	int		status;
	tls_session_t	*ssn;
	eap_tls_t	*inst;
	VALUE_PAIR	*vp;
	int		client_cert = TRUE;
	int		verify_mode = 0;
	REQUEST		*request = handler->request;

	inst = (eap_tls_t *)type_arg;

	handler->tls = TRUE;
	handler->finished = FALSE;


	if (inst->conf->session_cache_enable &&
	    ((inst->conf->session_last_flushed + (inst->conf->session_timeout * 1800)) <= request->timestamp)) {
		RDEBUG2("Flushing SSL sessions (of #%ld)",
			SSL_CTX_sess_number(inst->ctx));

		SSL_CTX_flush_sessions(inst->ctx, request->timestamp);
		inst->conf->session_last_flushed = request->timestamp;
	}


	if (handler->eap_type != PW_EAP_TLS) {
		vp = pairfind(handler->request->config_items,
			      PW_EAP_TLS_REQUIRE_CLIENT_CERT);
		if (!vp) {
			client_cert = FALSE;
		} else {
			client_cert = vp->vp_integer;
		}
	}


	ssn = eaptls_new_session(inst->ctx, client_cert);
	if (!ssn) {
		return 0;
	}


	if (client_cert) {
		RDEBUG2("Requiring client certificate");
		verify_mode = SSL_VERIFY_PEER;
		verify_mode |= SSL_VERIFY_FAIL_IF_NO_PEER_CERT;
		verify_mode |= SSL_VERIFY_CLIENT_ONCE;
	}
	SSL_set_verify(ssn->ssl, verify_mode, cbtls_verify);


	SSL_set_ex_data(ssn->ssl, 0, (void *)handler);
	SSL_set_ex_data(ssn->ssl, 1, (void *)inst->conf);
#ifdef HAVE_OPENSSL_OCSP_H
	SSL_set_ex_data(ssn->ssl, 2, (void *)inst->store);
#endif

	ssn->length_flag = inst->conf->include_length;


	ssn->offset = inst->conf->fragment_size;
	vp = pairfind(handler->request->packet->vps, PW_FRAMED_MTU);
	if (vp && ((vp->vp_integer - 14) < ssn->offset)) {


		ssn->offset = vp->vp_integer - 14;
	}

	handler->opaque = ((void *)ssn);
	handler->free_opaque = session_free;

	RDEBUG2("Initiate");


	switch (handler->eap_type) {
	case PW_EAP_TLS:
	default:
		ssn->prf_label = "client EAP encryption";
		break;

	case PW_EAP_TTLS:
		ssn->prf_label = "ttls keying material";
		break;


	case PW_EAP_PEAP:


		ssn->peap_flag = 0x00;


		ssn->length_flag = 0;

		ssn->prf_label = "client EAP encryption";
		break;
	}

	if (inst->conf->session_cache_enable) {
		ssn->allow_session_resumption = 1;
	}


	status = eaptls_start(handler->eap_ds, ssn->peap_flag);
	RDEBUG2("Start returned %d", status);
	if (status == 0)
		return 0;


	handler->stage = AUTHENTICATE;

	return 1;
}
