int http_process_req_common(struct stream *s, struct channel *req, int an_bit, struct proxy *px)
{
	struct list *def_rules, *rules;
	struct session *sess = s->sess;
	struct http_txn *txn = s->txn;
	struct http_msg *msg = &txn->req;
	struct htx *htx;
	struct redirect_rule *rule;
	enum rule_result verdict;
	struct connection *conn = objt_conn(sess->origin);

	DBG_TRACE_ENTER(STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn, msg);

	htx = htxbuf(&req->buf);


	if (!s->current_rule && !s->current_rule_list)
		stream_inc_be_http_req_ctr(s);

	def_rules = ((px->defpx && (an_bit == AN_REQ_HTTP_PROCESS_FE || px != sess->fe)) ? &px->defpx->http_req_rules : NULL);
	rules = &px->http_req_rules;


	if ((def_rules && !LIST_ISEMPTY(def_rules)) || !LIST_ISEMPTY(rules)) {
		verdict = http_req_get_intercept_rule(px, def_rules, rules, s);

		switch (verdict) {
		case HTTP_RULE_RES_YIELD:
			goto return_prx_yield;

		case HTTP_RULE_RES_CONT:
		case HTTP_RULE_RES_STOP:
			break;

		case HTTP_RULE_RES_DENY:
			if (txn->flags & TX_CLTARPIT)
				goto tarpit;
			goto deny;

		case HTTP_RULE_RES_ABRT:
			goto return_prx_cond;

		case HTTP_RULE_RES_DONE:
			goto done;

		case HTTP_RULE_RES_BADREQ:
			goto return_bad_req;

		case HTTP_RULE_RES_ERROR:
			goto return_int_err;
		}
	}

	if (conn && (conn->flags & CO_FL_EARLY_DATA) &&
	    (conn->flags & (CO_FL_EARLY_SSL_HS | CO_FL_SSL_WAIT_HS))) {
		struct http_hdr_ctx ctx;

		ctx.blk = NULL;
		if (!http_find_header(htx, ist("Early-Data"), &ctx, 0)) {
			if (unlikely(!http_add_header(htx, ist("Early-Data"), ist("1"))))
				goto return_int_err;
		}
	}


	if (!s->target && http_stats_check_uri(s, txn, px)) {
		s->target = &http_stats_applet.obj_type;
		if (unlikely(!si_register_handler(&s->si[1], objt_applet(s->target)))) {
			s->logs.tv_request = now;
			if (!(s->flags & SF_ERR_MASK))
				s->flags |= SF_ERR_RESOURCE;
			goto return_int_err;
		}


		http_handle_stats(s, req);
		verdict = http_req_get_intercept_rule(px, NULL, &px->uri_auth->http_req_rules, s);


		if (verdict == HTTP_RULE_RES_DENY)
			goto deny;

		if (verdict == HTTP_RULE_RES_ABRT)
			goto return_prx_cond;

		if (verdict == HTTP_RULE_RES_BADREQ)
			goto return_bad_req;

		if (verdict == HTTP_RULE_RES_ERROR)
			goto return_int_err;
	}


	if (unlikely(objt_applet(s->target))) {
		if (sess->fe == s->be)
			_HA_ATOMIC_INC(&sess->fe->fe_counters.intercepted_req);

		if (http_handle_expect_hdr(s, htx, msg) == -1)
			goto return_int_err;

		if (!(s->flags & SF_ERR_MASK))
			s->flags |= SF_ERR_LOCAL;
		if (!(s->flags & SF_FINST_MASK))
			s->flags |= SF_FINST_R;

		if (HAS_FILTERS(s))
			req->analysers |= AN_REQ_FLT_HTTP_HDRS;


		req->analysers &= (AN_REQ_HTTP_BODY | AN_REQ_FLT_HTTP_HDRS | AN_REQ_FLT_END);
		req->analysers &= ~AN_REQ_FLT_XFER_DATA;
		req->analysers |= AN_REQ_HTTP_XFER_BODY;

		req->flags |= CF_SEND_DONTWAIT;
		s->flags |= SF_ASSIGNED;
		goto done;
	}


	list_for_each_entry(rule, &px->redirect_rules, list) {
		if (rule->cond) {
			int ret;

			ret = acl_exec_cond(rule->cond, px, sess, s, SMP_OPT_DIR_REQ|SMP_OPT_FINAL);
			ret = acl_pass(ret);
			if (rule->cond->pol == ACL_COND_UNLESS)
				ret = !ret;
			if (!ret)
				continue;
		}
		if (!http_apply_redirect_rule(rule, s, txn))
			goto return_int_err;
		goto done;
	}


	req->flags |= CF_SEND_DONTWAIT;

 done:


	req->analyse_exp = TICK_ETERNITY;
 done_without_exp:
	req->analysers &= ~an_bit;
	s->current_rule = s->current_rule_list = NULL;
	DBG_TRACE_LEAVE(STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
	return 1;

 tarpit:


	if (s->be->cookie_name || sess->fe->capture_name)
		http_manage_client_side_cookies(s, req);


	channel_htx_erase(&s->req, htx);


	channel_dont_connect(req);

	req->analysers &= AN_REQ_FLT_END;
	req->analysers |= AN_REQ_HTTP_TARPIT;
	req->analyse_exp = tick_add_ifset(now_ms,  s->be->timeout.tarpit);
	if (!req->analyse_exp)
		req->analyse_exp = tick_add(now_ms, 0);
	stream_inc_http_err_ctr(s);
	_HA_ATOMIC_INC(&sess->fe->fe_counters.denied_req);
	if (s->flags & SF_BE_ASSIGNED)
		_HA_ATOMIC_INC(&s->be->be_counters.denied_req);
	if (sess->listener && sess->listener->counters)
		_HA_ATOMIC_INC(&sess->listener->counters->denied_req);
	goto done_without_exp;

 deny:


	if (s->be->cookie_name || sess->fe->capture_name)
		http_manage_client_side_cookies(s, req);

	s->logs.tv_request = now;
	stream_inc_http_err_ctr(s);
	_HA_ATOMIC_INC(&sess->fe->fe_counters.denied_req);
	if (s->flags & SF_BE_ASSIGNED)
		_HA_ATOMIC_INC(&s->be->be_counters.denied_req);
	if (sess->listener && sess->listener->counters)
		_HA_ATOMIC_INC(&sess->listener->counters->denied_req);
	goto return_prx_err;

 return_int_err:
	txn->status = 500;
	if (!(s->flags & SF_ERR_MASK))
		s->flags |= SF_ERR_INTERNAL;
	_HA_ATOMIC_INC(&sess->fe->fe_counters.internal_errors);
	if (s->flags & SF_BE_ASSIGNED)
		_HA_ATOMIC_INC(&s->be->be_counters.internal_errors);
	if (sess->listener && sess->listener->counters)
		_HA_ATOMIC_INC(&sess->listener->counters->internal_errors);
	goto return_prx_err;

 return_bad_req:
	txn->status = 400;
	_HA_ATOMIC_INC(&sess->fe->fe_counters.failed_req);
	if (sess->listener && sess->listener->counters)
		_HA_ATOMIC_INC(&sess->listener->counters->failed_req);


 return_prx_err:
	http_reply_and_close(s, txn->status, http_error_message(s));


 return_prx_cond:
	if (!(s->flags & SF_ERR_MASK))
		s->flags |= SF_ERR_PRXCOND;
	if (!(s->flags & SF_FINST_MASK))
		s->flags |= SF_FINST_R;

	req->analysers &= AN_REQ_FLT_END;
	req->analyse_exp = TICK_ETERNITY;
	s->current_rule = s->current_rule_list = NULL;
	DBG_TRACE_DEVEL("leaving on error",
			STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA|STRM_EV_HTTP_ERR, s, txn);
	return 0;

 return_prx_yield:
	channel_dont_connect(req);
	DBG_TRACE_DEVEL("waiting for more data",
			STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
	return 0;
}
