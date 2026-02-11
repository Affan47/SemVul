eappeap_postproxy(EAP_HANDLER *handler, void *data)
{
	int rcode;
	tls_session_t *tls_session = (tls_session_t *) data;
	REQUEST *fake, *request = handler->request;

	rad_assert(request != NULL);
	RDEBUG2("Passing reply from proxy back into the tunnel.");


	fake = (REQUEST *) request_data_get(handler->request,
					    handler->request->proxy,
					    REQUEST_DATA_EAP_MSCHAP_TUNNEL_CALLBACK);


	if (fake && (handler->request->proxy_reply->code == PW_AUTHENTICATION_ACK)) {
		peap_tunnel_t *t = tls_session->opaque;

		t->home_access_accept = TRUE;


		rad_assert(fake->packet == NULL);
		fake->packet = request->proxy;
		fake->packet->src_ipaddr = request->packet->src_ipaddr;
		request->proxy = NULL;

		rad_assert(fake->reply == NULL);
		fake->reply = request->proxy_reply;
		request->proxy_reply = NULL;

		if ((debug_flag > 0) && fr_log_fp) {
			fprintf(fr_log_fp, "server %s {\n", fake->server);
		}


		fake->options &= ~RAD_REQUEST_OPTION_PROXY_EAP;
		RDEBUG2("Passing reply back for EAP-MS-CHAP-V2");
		module_post_proxy(0, fake);


		rcode = rad_postauth(fake);

		if ((debug_flag > 0) && fr_log_fp) {
			fprintf(fr_log_fp, "} # server %s\n", fake->server);

			RDEBUG("Final reply from tunneled session code %d",
			       fake->reply->code);

			debug_pair_list(fake->reply->vps);
		}


		request->proxy = fake->packet;
		fake->packet = NULL;
		request->proxy_reply = fake->reply;
		fake->reply = NULL;


		switch (rcode) {
                case RLM_MODULE_FAIL:
			request_free(&fake);
			eaptls_fail(handler, 0);
			return 0;
			break;

                default:
			RDEBUG2("Got reply %d", request->proxy_reply->code);
			break;
		}
	}
	request_free(&fake);


	rcode = process_reply(handler, tls_session, handler->request,
			      handler->request->proxy_reply);


	pairfree(&handler->request->proxy_reply->vps);

	switch (rcode) {
	case RLM_MODULE_REJECT:
		RDEBUG2("Reply was rejected");
		eaptls_fail(handler, 0);
		return 0;

	case RLM_MODULE_HANDLED:
		RDEBUG2("Reply was handled");
		eaptls_request(handler->eap_ds, tls_session);
		return 1;

	case RLM_MODULE_OK:
		RDEBUG2("Reply was OK");


		return eaptls_success(handler, 0);

	default:
		RDEBUG2("Reply was unknown.");
		break;
	}

	eaptls_fail(handler, 0);
	return 0;
}
