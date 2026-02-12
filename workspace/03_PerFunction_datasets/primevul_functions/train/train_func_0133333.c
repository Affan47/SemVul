int http_wait_for_response(struct stream *s, struct channel *rep, int an_bit)
{


	struct session *sess = s->sess;
	struct http_txn *txn = s->txn;
	struct http_msg *msg = &txn->rsp;
	struct htx *htx;
	struct stream_interface *si_b = &s->si[1];
	struct connection *srv_conn;
	struct htx_sl *sl;
	int n;

	DBG_TRACE_ENTER(STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn, msg);

	htx = htxbuf(&rep->buf);


	if (htx->flags & HTX_FL_PARSING_ERROR)
		goto return_bad_res;
	if (htx->flags & HTX_FL_PROCESSING_ERROR)
		goto return_int_err;


  next_one:
	if (unlikely(htx_is_empty(htx) || htx->first == -1)) {

		if (rep->flags & CF_READ_ERROR) {
			struct connection *conn = NULL;

			if (objt_cs(s->si[1].end))
				conn = __objt_cs(s->si[1].end)->conn;


			if ((si_b->flags & SI_FL_L7_RETRY) &&
			    (s->be->retry_type & PR_RE_EARLY_ERROR) &&
			    conn && conn->err_code == CO_ER_SSL_EARLY_FAILED &&
			    do_l7_retry(s, si_b) == 0) {
				DBG_TRACE_DEVEL("leaving on L7 retry",
						STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
				return 0;
			}

			if (txn->flags & TX_NOT_FIRST)
				goto abort_keep_alive;

			_HA_ATOMIC_INC(&s->be->be_counters.failed_resp);
			if (objt_server(s->target)) {
				_HA_ATOMIC_INC(&__objt_server(s->target)->counters.failed_resp);
				health_adjust(__objt_server(s->target), HANA_STATUS_HTTP_READ_ERROR);
			}


			if (conn && conn->err_code == CO_ER_SSL_EARLY_FAILED)
				txn->status = 425;
			else {
				txn->status = 502;
				stream_inc_http_fail_ctr(s);
			}

			s->si[1].flags |= SI_FL_NOLINGER;
			http_reply_and_close(s, txn->status, http_error_message(s));

			if (!(s->flags & SF_ERR_MASK))
				s->flags |= SF_ERR_SRVCL;
			if (!(s->flags & SF_FINST_MASK))
				s->flags |= SF_FINST_H;
			DBG_TRACE_DEVEL("leaving on error",
					STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA|STRM_EV_HTTP_ERR, s, txn);
			return 0;
		}


		else if (rep->flags & CF_READ_TIMEOUT) {
			if ((si_b->flags & SI_FL_L7_RETRY) &&
			    (s->be->retry_type & PR_RE_TIMEOUT)) {
				if (co_data(rep) || do_l7_retry(s, si_b) == 0) {
					DBG_TRACE_DEVEL("leaving on L7 retry",
							STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
					return 0;
				}
			}
			_HA_ATOMIC_INC(&s->be->be_counters.failed_resp);
			if (objt_server(s->target)) {
				_HA_ATOMIC_INC(&__objt_server(s->target)->counters.failed_resp);
				health_adjust(__objt_server(s->target), HANA_STATUS_HTTP_READ_TIMEOUT);
			}

			txn->status = 504;
			stream_inc_http_fail_ctr(s);
			s->si[1].flags |= SI_FL_NOLINGER;
			http_reply_and_close(s, txn->status, http_error_message(s));

			if (!(s->flags & SF_ERR_MASK))
				s->flags |= SF_ERR_SRVTO;
			if (!(s->flags & SF_FINST_MASK))
				s->flags |= SF_FINST_H;
			DBG_TRACE_DEVEL("leaving on error",
					STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA|STRM_EV_HTTP_ERR, s, txn);
			return 0;
		}


		else if ((rep->flags & CF_SHUTR) && ((s->req.flags & (CF_SHUTR|CF_SHUTW)) == (CF_SHUTR|CF_SHUTW))) {
			_HA_ATOMIC_INC(&sess->fe->fe_counters.cli_aborts);
			_HA_ATOMIC_INC(&s->be->be_counters.cli_aborts);
			if (sess->listener && sess->listener->counters)
				_HA_ATOMIC_INC(&sess->listener->counters->cli_aborts);
			if (objt_server(s->target))
				_HA_ATOMIC_INC(&__objt_server(s->target)->counters.cli_aborts);

			txn->status = 400;
			http_reply_and_close(s, txn->status, http_error_message(s));

			if (!(s->flags & SF_ERR_MASK))
				s->flags |= SF_ERR_CLICL;
			if (!(s->flags & SF_FINST_MASK))
				s->flags |= SF_FINST_H;


			DBG_TRACE_DEVEL("leaving on error",
					STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA|STRM_EV_HTTP_ERR, s, txn);
			return 0;
		}


		else if (rep->flags & CF_SHUTR) {
			if ((si_b->flags & SI_FL_L7_RETRY) &&
			    (s->be->retry_type & PR_RE_DISCONNECTED)) {
				if (co_data(rep) || do_l7_retry(s, si_b) == 0) {
					DBG_TRACE_DEVEL("leaving on L7 retry",
							STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
					return 0;
				}
			}

			if (txn->flags & TX_NOT_FIRST)
				goto abort_keep_alive;

			_HA_ATOMIC_INC(&s->be->be_counters.failed_resp);
			if (objt_server(s->target)) {
				_HA_ATOMIC_INC(&__objt_server(s->target)->counters.failed_resp);
				health_adjust(__objt_server(s->target), HANA_STATUS_HTTP_BROKEN_PIPE);
			}

			txn->status = 502;
			stream_inc_http_fail_ctr(s);
			s->si[1].flags |= SI_FL_NOLINGER;
			http_reply_and_close(s, txn->status, http_error_message(s));

			if (!(s->flags & SF_ERR_MASK))
				s->flags |= SF_ERR_SRVCL;
			if (!(s->flags & SF_FINST_MASK))
				s->flags |= SF_FINST_H;
			DBG_TRACE_DEVEL("leaving on error",
					STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA|STRM_EV_HTTP_ERR, s, txn);
			return 0;
		}


		else if (rep->flags & CF_WRITE_ERROR) {
			if (txn->flags & TX_NOT_FIRST)
				goto abort_keep_alive;

			_HA_ATOMIC_INC(&s->be->be_counters.failed_resp);
			if (objt_server(s->target))
				_HA_ATOMIC_INC(&__objt_server(s->target)->counters.failed_resp);
			rep->analysers &= AN_RES_FLT_END;

			if (!(s->flags & SF_ERR_MASK))
				s->flags |= SF_ERR_CLICL;
			if (!(s->flags & SF_FINST_MASK))
				s->flags |= SF_FINST_H;


			DBG_TRACE_DEVEL("leaving on error",
					STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA|STRM_EV_HTTP_ERR, s, txn);
			return 0;
		}

		channel_dont_close(rep);
		rep->flags |= CF_READ_DONTWAIT;
		DBG_TRACE_DEVEL("waiting for more data",
				STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
		return 0;
	}


	BUG_ON(htx_get_first_type(htx) != HTX_BLK_RES_SL);
	sl = http_get_stline(htx);


	if ((si_b->flags & SI_FL_L7_RETRY) &&
	    l7_status_match(s->be, sl->info.res.status) &&
	    do_l7_retry(s, si_b) == 0) {
		DBG_TRACE_DEVEL("leaving on L7 retry", STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
		return 0;
	}


	b_free(&s->si[1].l7_buffer);

	msg->msg_state = HTTP_MSG_BODY;


	if (unlikely((global.mode & MODE_DEBUG) &&
		     (!(global.mode & MODE_QUIET) || (global.mode & MODE_VERBOSE)))) {
		int32_t pos;

		http_debug_stline("srvrep", s, sl);

		for (pos = htx_get_first(htx); pos != -1; pos = htx_get_next(htx, pos)) {
			struct htx_blk *blk = htx_get_blk(htx, pos);
			enum htx_blk_type type = htx_get_blk_type(blk);

			if (type == HTX_BLK_EOH)
				break;
			if (type != HTX_BLK_HDR)
				continue;

			http_debug_hdr("srvhdr", s,
				       htx_get_blk_name(htx, blk),
				       htx_get_blk_value(htx, blk));
		}
	}


	txn->status = sl->info.res.status;
	if (sl->flags & HTX_SL_F_VER_11)
                msg->flags |= HTTP_MSGF_VER_11;
	if (sl->flags & HTX_SL_F_XFER_LEN) {
		msg->flags |= HTTP_MSGF_XFER_LEN;
		if (sl->flags & HTX_SL_F_CLEN)
			msg->flags |= HTTP_MSGF_CNT_LEN;
		else if (sl->flags & HTX_SL_F_CHNK)
			msg->flags |= HTTP_MSGF_TE_CHNK;
	}
	if (sl->flags & HTX_SL_F_BODYLESS)
		msg->flags |= HTTP_MSGF_BODYLESS;
	if (sl->flags & HTX_SL_F_CONN_UPG)
		msg->flags |= HTTP_MSGF_CONN_UPG;

	n = txn->status / 100;
	if (n < 1 || n > 5)
		n = 0;


	if (n == 4)
		stream_inc_http_err_ctr(s);

	if (n == 5 && txn->status != 501 && txn->status != 505)
		stream_inc_http_fail_ctr(s);

	if (objt_server(s->target)) {
		_HA_ATOMIC_INC(&__objt_server(s->target)->counters.p.http.rsp[n]);
		_HA_ATOMIC_INC(&__objt_server(s->target)->counters.p.http.cum_req);
	}


	if (objt_server(s->target)) {
		if (txn->status >= 100 && (txn->status < 500 || txn->status == 501 || txn->status == 505))
			health_adjust(__objt_server(s->target), HANA_STATUS_HTTP_OK);
		else
			health_adjust(__objt_server(s->target), HANA_STATUS_HTTP_STS);
	}


	if (txn->status < 200 &&
	    (txn->status == 100 || txn->status >= 102)) {
		FLT_STRM_CB(s, flt_http_reset(s, msg));
		htx->first = channel_htx_fwd_headers(rep, htx);
		msg->msg_state = HTTP_MSG_RPBEFORE;
		msg->flags = 0;
		txn->status = 0;
		s->logs.t_data = -1;
		rep->flags |= CF_SEND_DONTWAIT;
		goto next_one;
	}


	if (txn->status == 101 &&
	    (!(txn->req.flags & HTTP_MSGF_CONN_UPG) || !(txn->rsp.flags & HTTP_MSGF_CONN_UPG)))
		goto return_bad_res;


	switch (txn->status) {
	case 200:
	case 203:
	case 204:
	case 206:
	case 300:
	case 301:
	case 404:
	case 405:
	case 410:
	case 414:
	case 501:
		break;
	default:


		txn->flags &= ~(TX_CACHEABLE | TX_CACHE_COOK);
		break;
	}


	s->logs.logwait &= ~LW_RESP;
	if (unlikely((s->logs.logwait & LW_RSPHDR) && s->res_cap))
		http_capture_headers(htx, s->res_cap, sess->fe->rsp_cap);


	if (unlikely((txn->meth == HTTP_METH_CONNECT && txn->status >= 200 && txn->status < 300) ||
		     txn->status == 101)) {


		txn->flags |= TX_CON_WANT_TUN;
	}


	srv_conn = cs_conn(objt_cs(s->si[1].end));
	if (srv_conn) {
		struct ist hdr;
		struct http_hdr_ctx ctx;

		if (txn->status == 401)
			hdr = ist("WWW-Authenticate");
		else if (txn->status == 407)
			hdr = ist("Proxy-Authenticate");
		else
			goto end;

		ctx.blk = NULL;
		while (http_find_header(htx, hdr, &ctx, 0)) {


			if ((ctx.value.len >= 4 && strncasecmp(ctx.value.ptr, "Nego", 4) == 0) ||
			    (ctx.value.len >= 4 && strncasecmp(ctx.value.ptr, "NTLM", 4) == 0)) {
				sess->flags |= SESS_FL_PREFER_LAST;
				conn_set_owner(srv_conn, sess, NULL);
				conn_set_private(srv_conn);

				session_add_conn(srv_conn->owner, srv_conn, srv_conn->target);
				break;
			}
		}
	}

  end:

	s->logs.t_data = tv_ms_elapsed(&s->logs.tv_accept, &now);


	rep->analysers &= ~an_bit;
	rep->analyse_exp = TICK_ETERNITY;
	channel_auto_close(rep);
	DBG_TRACE_LEAVE(STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
	return 1;

 return_int_err:
	_HA_ATOMIC_INC(&sess->fe->fe_counters.internal_errors);
	_HA_ATOMIC_INC(&s->be->be_counters.internal_errors);
	if (sess->listener && sess->listener->counters)
		_HA_ATOMIC_INC(&sess->listener->counters->internal_errors);
	if (objt_server(s->target))
		_HA_ATOMIC_INC(&__objt_server(s->target)->counters.internal_errors);
	txn->status = 500;
	if (!(s->flags & SF_ERR_MASK))
		s->flags |= SF_ERR_INTERNAL;
	goto return_prx_cond;

  return_bad_res:
	_HA_ATOMIC_INC(&s->be->be_counters.failed_resp);
	if (objt_server(s->target)) {
		_HA_ATOMIC_INC(&__objt_server(s->target)->counters.failed_resp);
		health_adjust(__objt_server(s->target), HANA_STATUS_HTTP_HDRRSP);
	}
	if ((s->be->retry_type & PR_RE_JUNK_REQUEST) &&
	    (si_b->flags & SI_FL_L7_RETRY) &&
	    do_l7_retry(s, si_b) == 0) {
		DBG_TRACE_DEVEL("leaving on L7 retry",
				STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
		return 0;
	}
	txn->status = 502;
	stream_inc_http_fail_ctr(s);


 return_prx_cond:
	http_reply_and_close(s, txn->status, http_error_message(s));

	if (!(s->flags & SF_ERR_MASK))
		s->flags |= SF_ERR_PRXCOND;
	if (!(s->flags & SF_FINST_MASK))
		s->flags |= SF_FINST_H;

	s->si[1].flags |= SI_FL_NOLINGER;
	DBG_TRACE_DEVEL("leaving on error",
			STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA|STRM_EV_HTTP_ERR, s, txn);
	return 0;

 abort_keep_alive:


	txn->status = 0;
	s->logs.logwait = 0;
	s->logs.level = 0;
	s->res.flags &= ~CF_EXPECT_MORE;
	http_reply_and_close(s, txn->status, NULL);
	DBG_TRACE_DEVEL("leaving by closing K/A connection",
			STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
	return 0;
}
