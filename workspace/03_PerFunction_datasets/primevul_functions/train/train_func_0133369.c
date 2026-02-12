int http_process_res_common(struct stream *s, struct channel *rep, int an_bit, struct proxy *px)
{
	struct session *sess = s->sess;
	struct http_txn *txn = s->txn;
	struct http_msg *msg = &txn->rsp;
	struct htx *htx;
	struct proxy *cur_proxy;
	enum rule_result ret = HTTP_RULE_RES_CONT;

	if (unlikely(msg->msg_state < HTTP_MSG_BODY))
		return 0;

	DBG_TRACE_ENTER(STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn, msg);

	htx = htxbuf(&rep->buf);


	if (unlikely(objt_applet(s->target) == &http_stats_applet)) {
		rep->analysers &= ~an_bit;
		rep->analyse_exp = TICK_ETERNITY;
		goto end;
	}


	if (s->current_rule_list == &sess->fe->http_res_rules ||
	    (sess->fe->defpx && s->current_rule_list == &sess->fe->defpx->http_res_rules))
		cur_proxy = sess->fe;
	else
		cur_proxy = s->be;

	while (1) {

		if (ret == HTTP_RULE_RES_CONT || ret == HTTP_RULE_RES_STOP) {
			struct list *def_rules, *rules;

			def_rules = ((cur_proxy->defpx && (cur_proxy == s->be || cur_proxy->defpx != s->be->defpx)) ? &cur_proxy->defpx->http_res_rules : NULL);
			rules = &cur_proxy->http_res_rules;

			ret = http_res_get_intercept_rule(cur_proxy, def_rules, rules, s);

			switch (ret) {
			case HTTP_RULE_RES_YIELD:
				goto return_prx_yield;

			case HTTP_RULE_RES_CONT:
			case HTTP_RULE_RES_STOP:
				break;

			case HTTP_RULE_RES_DENY:
				goto deny;

			case HTTP_RULE_RES_ABRT:
				goto return_prx_cond;

			case HTTP_RULE_RES_DONE:
				goto done;

			case HTTP_RULE_RES_BADREQ:
				goto return_bad_res;

			case HTTP_RULE_RES_ERROR:
				goto return_int_err;
			}

		}


		if (cur_proxy == sess->fe)
			break;
		cur_proxy = sess->fe;
	}


	if (unlikely(txn->status < 200 && txn->status != 101))
		goto end;


	if (s->be->cookie_name || sess->fe->capture_name || (s->be->options & PR_O_CHK_CACHE))
		http_manage_server_side_cookies(s, rep);


	if ((s->be->options & PR_O_CHK_CACHE) || (s->be->ck_opts & PR_CK_NOC))
		http_check_response_for_cacheability(s, rep);


	if (objt_server(s->target) && (s->be->ck_opts & PR_CK_INS) &&
	    !((txn->flags & TX_SCK_FOUND) && (s->be->ck_opts & PR_CK_PSV)) &&
	    (!(s->flags & SF_DIRECT) ||
	     ((s->be->cookie_maxidle || txn->cookie_last_date) &&
	      (!txn->cookie_last_date || (txn->cookie_last_date - date.tv_sec) < 0)) ||
	     (s->be->cookie_maxlife && !txn->cookie_first_date) ||
	     (!s->be->cookie_maxlife && txn->cookie_first_date)) &&
	    (!(s->be->ck_opts & PR_CK_POST) || (txn->meth == HTTP_METH_POST)) &&
	    !(s->flags & SF_IGNORE_PRST)) {


		if (!__objt_server(s->target)->cookie) {
			chunk_printf(&trash,
				     "%s=; Expires=Thu, 01-Jan-1970 00:00:01 GMT; path=/",
				     s->be->cookie_name);
		}
		else {
			chunk_printf(&trash, "%s=%s", s->be->cookie_name, __objt_server(s->target)->cookie);

			if (s->be->cookie_maxidle || s->be->cookie_maxlife) {

				trash.area[trash.data++] = COOKIE_DELIM_DATE;
				s30tob64((date.tv_sec+3) >> 2,
					 trash.area + trash.data);
				trash.data += 5;

				if (s->be->cookie_maxlife) {


					trash.area[trash.data++] = COOKIE_DELIM_DATE;
					s30tob64(txn->cookie_first_date ?
						 txn->cookie_first_date >> 2 :
						 (date.tv_sec+3) >> 2,
						 trash.area + trash.data);
					trash.data += 5;
				}
			}
			chunk_appendf(&trash, "; path=/");
		}

		if (s->be->cookie_domain)
			chunk_appendf(&trash, "; domain=%s", s->be->cookie_domain);

		if (s->be->ck_opts & PR_CK_HTTPONLY)
			chunk_appendf(&trash, "; HttpOnly");

		if (s->be->ck_opts & PR_CK_SECURE)
			chunk_appendf(&trash, "; Secure");

		if (s->be->cookie_attrs)
			chunk_appendf(&trash, "; %s", s->be->cookie_attrs);

		if (unlikely(!http_add_header(htx, ist("Set-Cookie"), ist2(trash.area, trash.data))))
			goto return_int_err;

		txn->flags &= ~TX_SCK_MASK;
		if (__objt_server(s->target)->cookie && (s->flags & SF_DIRECT))

			txn->flags |= TX_SCK_UPDATED;
		else
			txn->flags |= TX_SCK_INSERTED;


		if ((s->be->ck_opts & PR_CK_NOC) && (txn->flags & TX_CACHEABLE)) {

			txn->flags &= ~TX_CACHEABLE & ~TX_CACHE_COOK;

			if (unlikely(!http_add_header(htx, ist("Cache-control"), ist("private"))))
				goto return_int_err;
		}
	}


	if (((txn->flags & (TX_CACHEABLE | TX_CACHE_COOK | TX_SCK_PRESENT)) ==
	     (TX_CACHEABLE | TX_CACHE_COOK | TX_SCK_PRESENT)) &&
	    (s->be->options & PR_O_CHK_CACHE)) {


		ha_alert("Blocking cacheable cookie in response from instance %s, server %s.\n",
			 s->be->id, objt_server(s->target) ? __objt_server(s->target)->id : "<dispatch>");
		send_log(s->be, LOG_ALERT,
			 "Blocking cacheable cookie in response from instance %s, server %s.\n",
			 s->be->id, objt_server(s->target) ? __objt_server(s->target)->id : "<dispatch>");
		goto deny;
	}

  end:


	if (!http_eval_after_res_rules(s))
		goto return_int_err;


	if (HAS_FILTERS(s))
		rep->analysers |= AN_RES_FLT_HTTP_HDRS;


	rep->analysers &= ~AN_RES_FLT_XFER_DATA;
	rep->analysers |= AN_RES_HTTP_XFER_BODY;


	if (!LIST_ISEMPTY(&sess->fe->logformat) && !(s->logs.logwait & LW_BYTES)) {
		s->logs.t_close = s->logs.t_data;
		s->logs.bytes_out = htx->data;
		s->do_log(s);
		s->logs.bytes_out = 0;
	}

 done:
	DBG_TRACE_LEAVE(STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
	rep->analysers &= ~an_bit;
	rep->analyse_exp = TICK_ETERNITY;
	s->current_rule = s->current_rule_list = NULL;
	return 1;

 deny:
	_HA_ATOMIC_INC(&sess->fe->fe_counters.denied_resp);
	_HA_ATOMIC_INC(&s->be->be_counters.denied_resp);
	if (sess->listener && sess->listener->counters)
		_HA_ATOMIC_INC(&sess->listener->counters->denied_resp);
	if (objt_server(s->target))
		_HA_ATOMIC_INC(&__objt_server(s->target)->counters.denied_resp);
	goto return_prx_err;

 return_int_err:
	txn->status = 500;
	if (!(s->flags & SF_ERR_MASK))
		s->flags |= SF_ERR_INTERNAL;
	_HA_ATOMIC_INC(&sess->fe->fe_counters.internal_errors);
	_HA_ATOMIC_INC(&s->be->be_counters.internal_errors);
	if (sess->listener && sess->listener->counters)
		_HA_ATOMIC_INC(&sess->listener->counters->internal_errors);
	if (objt_server(s->target))
		_HA_ATOMIC_INC(&__objt_server(s->target)->counters.internal_errors);
	goto return_prx_err;

 return_bad_res:
	txn->status = 502;
	stream_inc_http_fail_ctr(s);
	_HA_ATOMIC_INC(&s->be->be_counters.failed_resp);
	if (objt_server(s->target)) {
		_HA_ATOMIC_INC(&__objt_server(s->target)->counters.failed_resp);
		health_adjust(__objt_server(s->target), HANA_STATUS_HTTP_RSP);
	}


 return_prx_err:
	http_reply_and_close(s, txn->status, http_error_message(s));


 return_prx_cond:
	s->logs.t_data = -1;
	s->si[1].flags |= SI_FL_NOLINGER;

	if (!(s->flags & SF_ERR_MASK))
		s->flags |= SF_ERR_PRXCOND;
	if (!(s->flags & SF_FINST_MASK))
		s->flags |= SF_FINST_H;

	rep->analysers &= AN_RES_FLT_END;
	s->req.analysers &= AN_REQ_FLT_END;
	rep->analyse_exp = TICK_ETERNITY;
	s->current_rule = s->current_rule_list = NULL;
	DBG_TRACE_DEVEL("leaving on error",
			STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA|STRM_EV_HTTP_ERR, s, txn);
	return 0;

 return_prx_yield:
	channel_dont_close(rep);
	DBG_TRACE_DEVEL("waiting for more data",
			STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
	return 0;
}
