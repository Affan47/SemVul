int http_process_request(struct session *s, struct buffer *req, int an_bit)
{
	struct http_txn *txn = &s->txn;
	struct http_msg *msg = &txn->req;

	if (unlikely(msg->msg_state < HTTP_MSG_BODY)) {

		buffer_dont_connect(req);
		return 0;
	}

	DPRINTF(stderr,"[%u] %s: session=%p b=%p, exp(r,w)=%u,%u bf=%08x bl=%d analysers=%02x\n",
		now_ms, __FUNCTION__,
		s,
		req,
		req->rex, req->wex,
		req->flags,
		req->l,
		req->analysers);


	if ((s->be->options & PR_O_HTTP_PROXY) && !(s->flags & SN_ADDR_SET)) {
		url2sa(msg->sol + msg->sl.rq.u, msg->sl.rq.u_l, &s->srv_addr);
	}


	if ((s->be->cookie_name || s->be->appsession_name || s->fe->capture_name)
	    && !(txn->flags & (TX_CLDENY|TX_CLTARPIT)))
		manage_client_side_cookies(s, req);


	if ((txn->sessid == NULL) && s->be->appsession_name && !(s->flags & SN_IGNORE_PRST)) {
		get_srv_from_appsession(s, msg->sol + msg->sl.rq.u, msg->sl.rq.u_l);
	}


	if ((s->fe->options | s->be->options) & PR_O_FWDFOR) {
		struct hdr_ctx ctx = { .idx = 0 };

		if (!((s->fe->options2 | s->be->options2) & PR_O2_FF_ALWAYS) &&
			http_find_header2(s->be->fwdfor_hdr_len ? s->be->fwdfor_hdr_name : s->fe->fwdfor_hdr_name,
			                  s->be->fwdfor_hdr_len ? s->be->fwdfor_hdr_len : s->fe->fwdfor_hdr_len,
			                  txn->req.sol, &txn->hdr_idx, &ctx)) {


		}
		else if (s->cli_addr.ss_family == AF_INET) {


			if ((!s->fe->except_mask.s_addr ||
			     (((struct sockaddr_in *)&s->cli_addr)->sin_addr.s_addr & s->fe->except_mask.s_addr)
			     != s->fe->except_net.s_addr) &&
			    (!s->be->except_mask.s_addr ||
			     (((struct sockaddr_in *)&s->cli_addr)->sin_addr.s_addr & s->be->except_mask.s_addr)
			     != s->be->except_net.s_addr)) {
				int len;
				unsigned char *pn;
				pn = (unsigned char *)&((struct sockaddr_in *)&s->cli_addr)->sin_addr;


				if (s->be->fwdfor_hdr_len) {
					len = s->be->fwdfor_hdr_len;
					memcpy(trash, s->be->fwdfor_hdr_name, len);
				} else {
					len = s->fe->fwdfor_hdr_len;
					memcpy(trash, s->fe->fwdfor_hdr_name, len);
				}
				len += sprintf(trash + len, ": %d.%d.%d.%d", pn[0], pn[1], pn[2], pn[3]);

				if (unlikely(http_header_add_tail2(req, &txn->req,
								   &txn->hdr_idx, trash, len) < 0))
					goto return_bad_req;
			}
		}
		else if (s->cli_addr.ss_family == AF_INET6) {


			int len;
			char pn[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6,
				  (const void *)&((struct sockaddr_in6 *)(&s->cli_addr))->sin6_addr,
				  pn, sizeof(pn));


			if (s->be->fwdfor_hdr_len) {
				len = s->be->fwdfor_hdr_len;
				memcpy(trash, s->be->fwdfor_hdr_name, len);
			} else {
				len = s->fe->fwdfor_hdr_len;
				memcpy(trash, s->fe->fwdfor_hdr_name, len);
			}
			len += sprintf(trash + len, ": %s", pn);

			if (unlikely(http_header_add_tail2(req, &txn->req,
							   &txn->hdr_idx, trash, len) < 0))
				goto return_bad_req;
		}
	}


	if ((s->fe->options | s->be->options) & PR_O_ORGTO) {


		if (s->cli_addr.ss_family == AF_INET) {


			if (!(s->flags & SN_FRT_ADDR_SET))
				get_frt_addr(s);

			if ((!s->fe->except_mask_to.s_addr ||
			     (((struct sockaddr_in *)&s->frt_addr)->sin_addr.s_addr & s->fe->except_mask_to.s_addr)
			     != s->fe->except_to.s_addr) &&
			    (!s->be->except_mask_to.s_addr ||
			     (((struct sockaddr_in *)&s->frt_addr)->sin_addr.s_addr & s->be->except_mask_to.s_addr)
			     != s->be->except_to.s_addr)) {
				int len;
				unsigned char *pn;
				pn = (unsigned char *)&((struct sockaddr_in *)&s->frt_addr)->sin_addr;


				if (s->be->orgto_hdr_len) {
					len = s->be->orgto_hdr_len;
					memcpy(trash, s->be->orgto_hdr_name, len);
				} else {
					len = s->fe->orgto_hdr_len;
					memcpy(trash, s->fe->orgto_hdr_name, len);
				}
				len += sprintf(trash + len, ": %d.%d.%d.%d", pn[0], pn[1], pn[2], pn[3]);

				if (unlikely(http_header_add_tail2(req, &txn->req,
								   &txn->hdr_idx, trash, len) < 0))
					goto return_bad_req;
			}
		}
	}


	if (((txn->flags & TX_CON_WANT_MSK) != TX_CON_WANT_TUN) ||
	    ((s->fe->options|s->be->options) & PR_O_HTTP_CLOSE)) {
		unsigned int want_flags = 0;

		if (txn->flags & TX_REQ_VER_11) {
			if (((txn->flags & TX_CON_WANT_MSK) >= TX_CON_WANT_SCL ||
			    ((s->fe->options|s->be->options) & PR_O_HTTP_CLOSE)) &&
			    !((s->fe->options2|s->be->options2) & PR_O2_FAKE_KA))
				want_flags |= TX_CON_CLO_SET;
		} else {
			if (((txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_KAL &&
			     !((s->fe->options|s->be->options) & PR_O_HTTP_CLOSE)) ||
			    ((s->fe->options2|s->be->options2) & PR_O2_FAKE_KA))
				want_flags |= TX_CON_KAL_SET;
		}

		if (want_flags != (txn->flags & (TX_CON_CLO_SET|TX_CON_KAL_SET)))
			http_change_connection_header(txn, msg, req, want_flags);
	}


	if (!(s->flags & (SN_ASSIGNED|SN_DIRECT)) &&
	    s->txn.meth == HTTP_METH_POST && s->be->url_param_name != NULL &&
	    s->be->url_param_post_limit != 0 &&
	    (txn->flags & (TX_REQ_CNT_LEN|TX_REQ_TE_CHNK))) {
		buffer_dont_connect(req);
		req->analysers |= AN_REQ_HTTP_BODY;
	}

	if (txn->flags & TX_REQ_XFER_LEN) {
		req->analysers |= AN_REQ_HTTP_XFER_BODY;
#ifdef TCP_QUICKACK


		if ((s->listener->options & LI_O_NOQUICKACK) &&
		    ((txn->flags & TX_REQ_TE_CHNK) ||
		     (msg->body_len > req->l - txn->req.eoh - 2)))
			setsockopt(s->si[0].fd, IPPROTO_TCP, TCP_QUICKACK, &one, sizeof(one));
#endif
	}


	req->analyse_exp = TICK_ETERNITY;
	req->analysers &= ~an_bit;

	s->logs.tv_request = now;

	return 1;

 return_bad_req:
	if (unlikely(msg->msg_state == HTTP_MSG_ERROR) || msg->err_pos >= 0) {


		http_capture_bad_message(&s->fe->invalid_req, s, req, msg, msg->msg_state, s->fe);
	}

	txn->req.msg_state = HTTP_MSG_ERROR;
	txn->status = 400;
	req->analysers = 0;
	stream_int_retnclose(req->prod, error_message(s, HTTP_ERR_400));

	s->fe->counters.failed_req++;
	if (s->listener->counters)
		s->listener->counters->failed_req++;

	if (!(s->flags & SN_ERR_MASK))
		s->flags |= SN_ERR_PRXCOND;
	if (!(s->flags & SN_FINST_MASK))
		s->flags |= SN_FINST_R;
	return 0;
}
