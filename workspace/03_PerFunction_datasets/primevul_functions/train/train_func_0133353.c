int http_wait_for_request(struct stream *s, struct channel *req, int an_bit)
{


	struct session *sess = s->sess;
	struct http_txn *txn = s->txn;
	struct http_msg *msg = &txn->req;
	struct htx *htx;
	struct htx_sl *sl;

	DBG_TRACE_ENTER(STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn, msg);

	if (unlikely(!IS_HTX_STRM(s))) {


		BUG_ON(!(s->flags & SF_IGNORE) || !c_empty(&s->req));


		channel_dont_connect(req);


		if (req->flags & CF_SHUTR) {
			s->logs.logwait = 0;
                        s->logs.level = 0;
			channel_abort(&s->req);
			channel_abort(&s->res);
			req->analysers &= AN_REQ_FLT_END;
			req->analyse_exp = TICK_ETERNITY;
			DBG_TRACE_LEAVE(STRM_EV_STRM_ANA, s);
			return 1;
		}
		DBG_TRACE_LEAVE(STRM_EV_STRM_ANA, s);
		return 0;
	}

	htx = htxbuf(&req->buf);


	if (htx->flags & (HTX_FL_PARSING_ERROR|HTX_FL_PROCESSING_ERROR)) {
		stream_inc_http_req_ctr(s);
		proxy_inc_fe_req_ctr(sess->listener, sess->fe);
		if (htx->flags & HTX_FL_PARSING_ERROR) {
			stream_inc_http_err_ctr(s);
			goto return_bad_req;
		}
		else
			goto return_int_err;
	}


	s->srv_error = http_return_srv_error;

	msg->msg_state = HTTP_MSG_BODY;
	stream_inc_http_req_ctr(s);
	proxy_inc_fe_req_ctr(sess->listener, sess->fe);


	req->analyse_exp = TICK_ETERNITY;

	BUG_ON(htx_get_first_type(htx) != HTX_BLK_REQ_SL);
	sl = http_get_stline(htx);


	if (unlikely((global.mode & MODE_DEBUG) &&
		     (!(global.mode & MODE_QUIET) || (global.mode & MODE_VERBOSE)))) {
		int32_t pos;

		http_debug_stline("clireq", s, sl);

		for (pos = htx_get_first(htx); pos != -1; pos = htx_get_next(htx, pos)) {
			struct htx_blk *blk = htx_get_blk(htx, pos);
			enum htx_blk_type type = htx_get_blk_type(blk);

			if (type == HTX_BLK_EOH)
				break;
			if (type != HTX_BLK_HDR)
				continue;

			http_debug_hdr("clihdr", s,
				       htx_get_blk_name(htx, blk),
				       htx_get_blk_value(htx, blk));
		}
	}


	txn->meth = sl->info.req.meth;
	if (sl->flags & HTX_SL_F_VER_11)
                msg->flags |= HTTP_MSGF_VER_11;
	msg->flags |= HTTP_MSGF_XFER_LEN;
	if (sl->flags & HTX_SL_F_CLEN)
		msg->flags |= HTTP_MSGF_CNT_LEN;
	else if (sl->flags & HTX_SL_F_CHNK)
		msg->flags |= HTTP_MSGF_TE_CHNK;
	if (sl->flags & HTX_SL_F_BODYLESS)
		msg->flags |= HTTP_MSGF_BODYLESS;
	if (sl->flags & HTX_SL_F_CONN_UPG)
		msg->flags |= HTTP_MSGF_CONN_UPG;


	if (txn->meth == HTTP_METH_GET || txn->meth == HTTP_METH_HEAD)
		s->flags |= SF_REDIRECTABLE;
	else if (txn->meth == HTTP_METH_OTHER && isteqi(htx_sl_req_meth(sl), ist("PRI"))) {

		goto return_bad_req;
	}


	if (unlikely(sess->fe->monitor_uri_len != 0)) {
		const struct ist monitor_uri = ist2(sess->fe->monitor_uri,
		                                    sess->fe->monitor_uri_len);
		struct http_uri_parser parser = http_uri_parser_init(htx_sl_req_uri(sl));

		if ((istptr(monitor_uri)[0] == '/' &&
		     isteq(http_parse_path(&parser), monitor_uri)) ||
		    isteq(htx_sl_req_uri(sl), monitor_uri)) {


			struct acl_cond *cond;

			s->flags |= SF_MONITOR;
			_HA_ATOMIC_INC(&sess->fe->fe_counters.intercepted_req);


			list_for_each_entry(cond, &sess->fe->mon_fail_cond, list) {
				int ret = acl_exec_cond(cond, sess->fe, sess, s, SMP_OPT_DIR_REQ|SMP_OPT_FINAL);

				ret = acl_pass(ret);
				if (cond->pol == ACL_COND_UNLESS)
					ret = !ret;

				if (ret) {

					txn->status = 503;
					if (!(s->flags & SF_ERR_MASK))
						s->flags |= SF_ERR_LOCAL;
					goto return_prx_cond;
				}
			}


			txn->status = 200;
			if (!(s->flags & SF_ERR_MASK))
				s->flags |= SF_ERR_LOCAL;
			goto return_prx_cond;
		}
	}


	if (unlikely(s->logs.logwait & LW_REQ)) {

		if ((txn->uri = pool_alloc(pool_head_requri)) != NULL) {
			size_t len;

			len = http_fmt_req_line(sl, txn->uri, global.tune.requri_len - 1);
			txn->uri[len] = 0;

			if (!(s->logs.logwait &= ~(LW_REQ|LW_INIT)))
				s->do_log(s);
		} else {
			ha_alert("HTTP logging : out of memory.\n");
		}
	}


	if ((sess->fe->options2 & PR_O2_USE_PXHDR) &&
	    *HTX_SL_REQ_UPTR(sl) != '/' && *HTX_SL_REQ_UPTR(sl) != '*')
		txn->flags |= TX_USE_PX_CONN;


	if (unlikely((s->logs.logwait & LW_REQHDR) && s->req_cap))
		http_capture_headers(htx, s->req_cap, sess->fe->req_cap);


	if (s->be->options & PR_O_WREQ_BODY)
		req->analysers |= AN_REQ_HTTP_BODY;


	if (likely(txn->meth == HTTP_METH_GET ||
		   txn->meth == HTTP_METH_HEAD ||
		   txn->meth == HTTP_METH_OPTIONS ||
		   txn->meth == HTTP_METH_TRACE))
		txn->flags |= TX_CACHEABLE | TX_CACHE_COOK;


	req->analysers &= ~an_bit;
	req->analyse_exp = TICK_ETERNITY;

	DBG_TRACE_LEAVE(STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
	return 1;

 return_int_err:
	txn->status = 500;
	if (!(s->flags & SF_ERR_MASK))
		s->flags |= SF_ERR_INTERNAL;
	_HA_ATOMIC_INC(&sess->fe->fe_counters.internal_errors);
	if (sess->listener && sess->listener->counters)
		_HA_ATOMIC_INC(&sess->listener->counters->internal_errors);
	goto return_prx_cond;

 return_bad_req:
	txn->status = 400;
	_HA_ATOMIC_INC(&sess->fe->fe_counters.failed_req);
	if (sess->listener && sess->listener->counters)
		_HA_ATOMIC_INC(&sess->listener->counters->failed_req);


 return_prx_cond:
	http_reply_and_close(s, txn->status, http_error_message(s));

	if (!(s->flags & SF_ERR_MASK))
		s->flags |= SF_ERR_PRXCOND;
	if (!(s->flags & SF_FINST_MASK))
		s->flags |= SF_FINST_R;

	DBG_TRACE_DEVEL("leaving on error",
			STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA|STRM_EV_HTTP_ERR, s, txn);
	return 0;
}
