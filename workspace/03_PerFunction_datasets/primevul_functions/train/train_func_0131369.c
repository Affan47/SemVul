int http_process_req_common(struct session *s, struct channel *req, int an_bit, struct proxy *px)
{
	struct http_txn *txn = &s->txn;
	struct http_msg *msg = &txn->req;
	struct acl_cond *cond;
	struct http_req_rule *http_req_last_rule = NULL;
	struct redirect_rule *rule;
	struct cond_wordlist *wl;
	int do_stats;

	if (unlikely(msg->msg_state < HTTP_MSG_BODY)) {

		channel_dont_connect(req);
		return 0;
	}

	req->analysers &= ~an_bit;
	req->analyse_exp = TICK_ETERNITY;

	DPRINTF(stderr,"[%u] %s: session=%p b=%p, exp(r,w)=%u,%u bf=%08x bh=%d analysers=%02x\n",
		now_ms, __FUNCTION__,
		s,
		req,
		req->rex, req->wex,
		req->flags,
		req->buf->i,
		req->analysers);


	list_for_each_entry(cond, &px->block_cond, list) {
		int ret = acl_exec_cond(cond, px, s, txn, SMP_OPT_DIR_REQ|SMP_OPT_FINAL);

		ret = acl_pass(ret);
		if (cond->pol == ACL_COND_UNLESS)
			ret = !ret;

		if (ret) {
			txn->status = 403;

			s->logs.tv_request = now;
			stream_int_retnclose(req->prod, http_error_message(s, HTTP_ERR_403));
			session_inc_http_err_ctr(s);
			goto return_prx_cond;
		}
	}


	session_inc_be_http_req_ctr(s);


	http_req_last_rule = http_req_get_intercept_rule(px, &px->http_req_rules, s, txn);


	if (!http_req_last_rule) {
		do_stats = stats_check_uri(s->rep->prod, txn, px);
		if (do_stats)
			http_req_last_rule = http_req_get_intercept_rule(px, &px->uri_auth->http_req_rules, s, txn);
	}
	else
		do_stats = 0;


	if (txn->flags & (TX_CLDENY|TX_CLTARPIT)) {
		if (txn->flags & TX_CLDENY) {
			txn->status = 403;
			s->logs.tv_request = now;
			stream_int_retnclose(req->prod, http_error_message(s, HTTP_ERR_403));
			session_inc_http_err_ctr(s);
			s->fe->fe_counters.denied_req++;
			if (an_bit == AN_REQ_HTTP_PROCESS_BE)
				s->be->be_counters.denied_req++;
			if (s->listener->counters)
				s->listener->counters->denied_req++;
			goto return_prx_cond;
		}


		if (txn->flags & TX_CLTARPIT) {
			channel_erase(s->req);


			channel_dont_connect(req);
			req->analysers = 0;
			req->analysers |= AN_REQ_HTTP_TARPIT;
			req->analyse_exp = tick_add_ifset(now_ms,  s->be->timeout.tarpit);
			if (!req->analyse_exp)
				req->analyse_exp = tick_add(now_ms, 0);
			session_inc_http_err_ctr(s);
			s->fe->fe_counters.denied_req++;
			if (s->fe != s->be)
				s->be->be_counters.denied_req++;
			if (s->listener->counters)
				s->listener->counters->denied_req++;
			return 1;
		}
	}


	if (px->req_exp != NULL) {
		if (apply_filters_to_request(s, req, px) < 0)
			goto return_bad_req;


		if (txn->flags & TX_CLDENY) {

			txn->status = 403;

			s->logs.tv_request = now;
			stream_int_retnclose(req->prod, http_error_message(s, HTTP_ERR_403));
			session_inc_http_err_ctr(s);
			goto return_prx_cond;
		}


		if (txn->flags & TX_CLTARPIT) {
			channel_erase(s->req);


			channel_dont_connect(req);
			req->analysers = 0;
			req->analysers |= AN_REQ_HTTP_TARPIT;
			req->analyse_exp = tick_add_ifset(now_ms,  s->be->timeout.tarpit);
			if (!req->analyse_exp)
				req->analyse_exp = tick_add(now_ms, 0);
			session_inc_http_err_ctr(s);
			return 1;
		}
	}


	if ((!(txn->flags & TX_HDR_CONN_PRS) &&
	     (s->fe->options & (PR_O_KEEPALIVE|PR_O_SERVER_CLO|PR_O_HTTP_CLOSE|PR_O_FORCE_CLO))) ||
	    ((s->fe->options & (PR_O_KEEPALIVE|PR_O_SERVER_CLO|PR_O_HTTP_CLOSE|PR_O_FORCE_CLO)) !=
	     (s->be->options & (PR_O_KEEPALIVE|PR_O_SERVER_CLO|PR_O_HTTP_CLOSE|PR_O_FORCE_CLO)))) {
		int tmp = TX_CON_WANT_TUN;

		if ((s->fe->options|s->be->options) & PR_O_KEEPALIVE ||
		    ((s->fe->options2|s->be->options2) & PR_O2_FAKE_KA))
			tmp = TX_CON_WANT_KAL;
		if ((s->fe->options|s->be->options) & PR_O_SERVER_CLO)
			tmp = TX_CON_WANT_SCL;
		if ((s->fe->options|s->be->options) & PR_O_FORCE_CLO)
			tmp = TX_CON_WANT_CLO;

		if ((txn->flags & TX_CON_WANT_MSK) < tmp)
			txn->flags = (txn->flags & ~TX_CON_WANT_MSK) | tmp;

		if (!(txn->flags & TX_HDR_CONN_PRS)) {

			int to_del = 0;
			if ((msg->flags & HTTP_MSGF_VER_11) ||
			    ((txn->flags & TX_CON_WANT_MSK) >= TX_CON_WANT_SCL &&
			     !((s->fe->options2|s->be->options2) & PR_O2_FAKE_KA)))
				to_del |= 2;
			if (!(msg->flags & HTTP_MSGF_VER_11))
				to_del |= 1;
			http_parse_connection_header(txn, msg, to_del);
		}


		if (((txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_KAL ||
		     (txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_SCL) &&
		    ((txn->flags & TX_HDR_CONN_CLO) ||
		     (!(msg->flags & HTTP_MSGF_VER_11) && !(txn->flags & TX_HDR_CONN_KAL)) ||
		     ((s->fe->options|s->be->options) & PR_O_HTTP_CLOSE) ||
		     !(msg->flags & HTTP_MSGF_XFER_LEN) ||
		     s->fe->state == PR_STSTOPPED))
		    txn->flags = (txn->flags & ~TX_CON_WANT_MSK) | TX_CON_WANT_CLO;
	}


	if (http_req_last_rule && http_req_last_rule->action == HTTP_REQ_ACT_AUTH) {
		char *realm = http_req_last_rule->arg.auth.realm;

		if (!realm)
			realm = do_stats?STATS_DEFAULT_REALM:px->id;

		chunk_printf(&trash, (txn->flags & TX_USE_PX_CONN) ? HTTP_407_fmt : HTTP_401_fmt, realm);
		txn->status = 401;
		stream_int_retnclose(req->prod, &trash);


		session_inc_http_err_ctr(s);
		goto return_prx_cond;
	}


	list_for_each_entry(wl, &px->req_add, list) {
		if (wl->cond) {
			int ret = acl_exec_cond(wl->cond, px, s, txn, SMP_OPT_DIR_REQ|SMP_OPT_FINAL);
			ret = acl_pass(ret);
			if (((struct acl_cond *)wl->cond)->pol == ACL_COND_UNLESS)
				ret = !ret;
			if (!ret)
				continue;
		}

		if (unlikely(http_header_add_tail(&txn->req, &txn->hdr_idx, wl->s) < 0))
			goto return_bad_req;
	}

	if (http_req_last_rule && http_req_last_rule->action == HTTP_REQ_ACT_REDIR) {
		if (!http_apply_redirect_rule(http_req_last_rule->arg.redir, s, txn))
			goto return_bad_req;
		req->analyse_exp = TICK_ETERNITY;
		return 1;
	}

	if (unlikely(do_stats)) {

		if (!http_handle_stats(s, req)) {

			req->analysers |= an_bit;
			channel_dont_connect(req);
		}
		return 1;
	}


	list_for_each_entry(rule, &px->redirect_rules, list) {
		if (rule->cond) {
			int ret;

			ret = acl_exec_cond(rule->cond, px, s, txn, SMP_OPT_DIR_REQ|SMP_OPT_FINAL);
			ret = acl_pass(ret);
			if (rule->cond->pol == ACL_COND_UNLESS)
				ret = !ret;
			if (!ret)
				continue;
		}
		if (!http_apply_redirect_rule(rule, s, txn))
			goto return_bad_req;

		req->analyse_exp = TICK_ETERNITY;
		return 1;
	}


	req->flags |= CF_SEND_DONTWAIT;


	return 1;

 return_bad_req:

	if (unlikely(msg->msg_state == HTTP_MSG_ERROR) || msg->err_pos >= 0) {


		http_capture_bad_message(&s->fe->invalid_req, s, msg, msg->msg_state, s->fe);
	}

	txn->req.msg_state = HTTP_MSG_ERROR;
	txn->status = 400;
	stream_int_retnclose(req->prod, http_error_message(s, HTTP_ERR_400));

	s->fe->fe_counters.failed_req++;
	if (s->listener->counters)
		s->listener->counters->failed_req++;

 return_prx_cond:
	if (!(s->flags & SN_ERR_MASK))
		s->flags |= SN_ERR_PRXCOND;
	if (!(s->flags & SN_FINST_MASK))
		s->flags |= SN_FINST_R;

	req->analysers = 0;
	req->analyse_exp = TICK_ETERNITY;
	return 0;
}
