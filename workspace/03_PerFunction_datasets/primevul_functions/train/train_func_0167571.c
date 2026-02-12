int http_wait_for_request(struct session *s, struct buffer *req, int an_bit)
{


	int cur_idx;
	int use_close_only;
	struct http_txn *txn = &s->txn;
	struct http_msg *msg = &txn->req;
	struct hdr_ctx ctx;

	DPRINTF(stderr,"[%u] %s: session=%p b=%p, exp(r,w)=%u,%u bf=%08x bl=%d analysers=%02x\n",
		now_ms, __FUNCTION__,
		s,
		req,
		req->rex, req->wex,
		req->flags,
		req->l,
		req->analysers);


	s->srv_error = http_return_srv_error;


	if (req->l && msg->msg_state < HTTP_MSG_ERROR) {
		if ((txn->flags & TX_NOT_FIRST) &&
		    unlikely((req->flags & BF_FULL) ||
			     req->r < req->lr ||
			     req->r > req->data + req->size - global.tune.maxrewrite)) {
			if (req->send_max) {
				if (req->flags & (BF_SHUTW|BF_SHUTW_NOW|BF_WRITE_ERROR|BF_WRITE_TIMEOUT))
					goto failed_keep_alive;

				buffer_dont_connect(req);
				req->flags |= BF_READ_DONTWAIT;
				return 0;
			}
			if (req->l <= req->size - global.tune.maxrewrite)
				http_buffer_heavy_realign(req, msg);
		}


		if ((txn->flags & TX_NOT_FIRST) &&
		    unlikely((s->rep->flags & BF_FULL) ||
			     s->rep->r < s->rep->lr ||
			     s->rep->r > s->rep->data + s->rep->size - global.tune.maxrewrite)) {
			if (s->rep->send_max) {
				if (s->rep->flags & (BF_SHUTW|BF_SHUTW_NOW|BF_WRITE_ERROR|BF_WRITE_TIMEOUT))
					goto failed_keep_alive;

				buffer_dont_connect(req);
				s->rep->flags &= ~BF_EXPECT_MORE;
				return 0;
			}
		}

		if (likely(req->lr < req->r))
			http_msg_analyzer(req, msg, &txn->hdr_idx);
	}


	if (unlikely((global.mode & MODE_DEBUG) &&
		     (!(global.mode & MODE_QUIET) || (global.mode & MODE_VERBOSE)) &&
		     msg->sol &&
		     (msg->msg_state >= HTTP_MSG_BODY || msg->msg_state == HTTP_MSG_ERROR))) {
		char *eol, *sol;

		sol = req->data + msg->som;
		eol = sol + msg->sl.rq.l;
		debug_hdr("clireq", s, sol, eol);

		sol += hdr_idx_first_pos(&txn->hdr_idx);
		cur_idx = hdr_idx_first_idx(&txn->hdr_idx);

		while (cur_idx) {
			eol = sol + txn->hdr_idx.v[cur_idx].len;
			debug_hdr("clihdr", s, sol, eol);
			sol = eol + txn->hdr_idx.v[cur_idx].cr + 1;
			cur_idx = txn->hdr_idx.v[cur_idx].next;
		}
	}


	if (unlikely(msg->msg_state < HTTP_MSG_BODY)) {


		if (unlikely(msg->msg_state == HTTP_MSG_ERROR)) {
			proxy_inc_fe_req_ctr(s->fe);
			goto return_bad_req;
		}


		if (unlikely(req->flags & BF_FULL)) {


			proxy_inc_fe_req_ctr(s->fe);
			if (msg->err_pos < 0)
				msg->err_pos = req->l;
			goto return_bad_req;
		}


		else if (req->flags & BF_READ_ERROR) {
			if (!(s->flags & SN_ERR_MASK))
				s->flags |= SN_ERR_CLICL;

			if (txn->flags & TX_WAIT_NEXT_RQ)
				goto failed_keep_alive;


			if (msg->err_pos >= 0)
				http_capture_bad_message(&s->fe->invalid_req, s, req, msg, msg->msg_state, s->fe);

			txn->status = 400;
			stream_int_retnclose(req->prod, NULL);
			msg->msg_state = HTTP_MSG_ERROR;
			req->analysers = 0;

			proxy_inc_fe_req_ctr(s->fe);
			s->fe->counters.failed_req++;
			if (s->listener->counters)
				s->listener->counters->failed_req++;

			if (!(s->flags & SN_FINST_MASK))
				s->flags |= SN_FINST_R;
			return 0;
		}


		else if (req->flags & BF_READ_TIMEOUT || tick_is_expired(req->analyse_exp, now_ms)) {
			if (!(s->flags & SN_ERR_MASK))
				s->flags |= SN_ERR_CLITO;

			if (txn->flags & TX_WAIT_NEXT_RQ)
				goto failed_keep_alive;


			if (msg->err_pos >= 0)
				http_capture_bad_message(&s->fe->invalid_req, s, req, msg, msg->msg_state, s->fe);
			txn->status = 408;
			stream_int_retnclose(req->prod, error_message(s, HTTP_ERR_408));
			msg->msg_state = HTTP_MSG_ERROR;
			req->analysers = 0;

			proxy_inc_fe_req_ctr(s->fe);
			s->fe->counters.failed_req++;
			if (s->listener->counters)
				s->listener->counters->failed_req++;

			if (!(s->flags & SN_FINST_MASK))
				s->flags |= SN_FINST_R;
			return 0;
		}


		else if (req->flags & BF_SHUTR) {
			if (!(s->flags & SN_ERR_MASK))
				s->flags |= SN_ERR_CLICL;

			if (txn->flags & TX_WAIT_NEXT_RQ)
				goto failed_keep_alive;

			if (msg->err_pos >= 0)
				http_capture_bad_message(&s->fe->invalid_req, s, req, msg, msg->msg_state, s->fe);
			txn->status = 400;
			stream_int_retnclose(req->prod, error_message(s, HTTP_ERR_400));
			msg->msg_state = HTTP_MSG_ERROR;
			req->analysers = 0;

			proxy_inc_fe_req_ctr(s->fe);
			s->fe->counters.failed_req++;
			if (s->listener->counters)
				s->listener->counters->failed_req++;

			if (!(s->flags & SN_FINST_MASK))
				s->flags |= SN_FINST_R;
			return 0;
		}

		buffer_dont_connect(req);
		req->flags |= BF_READ_DONTWAIT;
		s->rep->flags &= ~BF_EXPECT_MORE;
#ifdef TCP_QUICKACK
		if (s->listener->options & LI_O_NOQUICKACK) {


			setsockopt(s->si[0].fd, IPPROTO_TCP, TCP_QUICKACK, &one, sizeof(one));
		}
#endif

		if ((msg->msg_state != HTTP_MSG_RQBEFORE) && (txn->flags & TX_WAIT_NEXT_RQ)) {


			txn->flags &= ~TX_WAIT_NEXT_RQ;
			req->analyse_exp = TICK_ETERNITY;
		}


		if (!tick_isset(req->analyse_exp)) {
			if ((msg->msg_state == HTTP_MSG_RQBEFORE) &&
			    (txn->flags & TX_WAIT_NEXT_RQ) &&
			    tick_isset(s->be->timeout.httpka))
				req->analyse_exp = tick_add(now_ms, s->be->timeout.httpka);
			else
				req->analyse_exp = tick_add_ifset(now_ms, s->be->timeout.httpreq);
		}


		return 0;

	failed_keep_alive:


		txn->status = 0;
		msg->msg_state = HTTP_MSG_RQBEFORE;
		req->analysers = 0;
		s->logs.logwait = 0;
		s->rep->flags &= ~BF_EXPECT_MORE;
		stream_int_retnclose(req->prod, NULL);
		return 0;
	}


	proxy_inc_fe_req_ctr(s->fe);

	if (txn->flags & TX_WAIT_NEXT_RQ) {

		txn->flags &= ~TX_WAIT_NEXT_RQ;
		req->analyse_exp = TICK_ETERNITY;
	}


	if (unlikely(msg->err_pos >= 0))
		http_capture_bad_message(&s->fe->invalid_req, s, req, msg, msg->msg_state, s->fe);


	txn->meth = find_http_meth(msg->sol, msg->sl.rq.m_l);


	if (txn->meth == HTTP_METH_GET || txn->meth == HTTP_METH_HEAD)
		s->flags |= SN_REDIRECTABLE;


	if (unlikely((s->fe->monitor_uri_len != 0) &&
		     (s->fe->monitor_uri_len == msg->sl.rq.u_l) &&
		     !memcmp(msg->sol + msg->sl.rq.u,
			     s->fe->monitor_uri,
			     s->fe->monitor_uri_len))) {


		struct acl_cond *cond;

		s->flags |= SN_MONITOR;


		list_for_each_entry(cond, &s->fe->mon_fail_cond, list) {
			int ret = acl_exec_cond(cond, s->fe, s, txn, ACL_DIR_REQ);

			ret = acl_pass(ret);
			if (cond->pol == ACL_COND_UNLESS)
				ret = !ret;

			if (ret) {

				txn->status = 503;
				stream_int_retnclose(req->prod, error_message(s, HTTP_ERR_503));
				goto return_prx_cond;
			}
		}


		txn->status = 200;
		stream_int_retnclose(req->prod, error_message(s, HTTP_ERR_200));
		goto return_prx_cond;
	}


	if (unlikely(s->logs.logwait & LW_REQ)) {

		if ((txn->uri = pool_alloc2(pool2_requri)) != NULL) {
			int urilen = msg->sl.rq.l;

			if (urilen >= REQURI_LEN)
				urilen = REQURI_LEN - 1;
			memcpy(txn->uri, &req->data[msg->som], urilen);
			txn->uri[urilen] = 0;

			if (!(s->logs.logwait &= ~LW_REQ))
				s->do_log(s);
		} else {
			Alert("HTTP logging : out of memory.\n");
		}
	}


	if (unlikely(msg->sl.rq.v_l == 0) && !http_upgrade_v09_to_v10(req, msg, txn))
		goto return_bad_req;


	if ((msg->sl.rq.v_l == 8) &&
	    ((msg->sol[msg->sl.rq.v + 5] > '1') ||
	     ((msg->sol[msg->sl.rq.v + 5] == '1') &&
	      (msg->sol[msg->sl.rq.v + 7] >= '1'))))
		txn->flags |= TX_REQ_VER_11;


	txn->flags &= ~(TX_HDR_CONN_PRS | TX_HDR_CONN_CLO | TX_HDR_CONN_KAL);


	if ((s->fe->options2 & PR_O2_USE_PXHDR) &&
	    msg->sol[msg->sl.rq.u] != '/' && msg->sol[msg->sl.rq.u] != '*')
		txn->flags |= TX_USE_PX_CONN;


	txn->flags &= ~TX_REQ_XFER_LEN;


	if (unlikely((s->logs.logwait & LW_REQHDR) && txn->req.cap))
		capture_headers(msg->sol, &txn->hdr_idx,
				txn->req.cap, s->fe->req_cap);


	use_close_only = 0;
	ctx.idx = 0;

	while ((txn->flags & TX_REQ_VER_11) &&
	       http_find_header2("Transfer-Encoding", 17, msg->sol, &txn->hdr_idx, &ctx)) {
		if (ctx.vlen == 7 && strncasecmp(ctx.line + ctx.val, "chunked", 7) == 0)
			txn->flags |= (TX_REQ_TE_CHNK | TX_REQ_XFER_LEN);
		else if (txn->flags & TX_REQ_TE_CHNK) {

			use_close_only = 1;
			txn->flags &= ~(TX_REQ_TE_CHNK | TX_REQ_XFER_LEN);
			break;
		}
	}

	ctx.idx = 0;
	while (!(txn->flags & TX_REQ_TE_CHNK) && !use_close_only &&
	       http_find_header2("Content-Length", 14, msg->sol, &txn->hdr_idx, &ctx)) {
		signed long long cl;

		if (!ctx.vlen) {
			msg->err_pos = ctx.line + ctx.val - req->data;
			goto return_bad_req;
		}

		if (strl2llrc(ctx.line + ctx.val, ctx.vlen, &cl)) {
			msg->err_pos = ctx.line + ctx.val - req->data;
			goto return_bad_req;
		}

		if (cl < 0) {
			msg->err_pos = ctx.line + ctx.val - req->data;
			goto return_bad_req;
		}

		if ((txn->flags & TX_REQ_CNT_LEN) && (msg->chunk_len != cl)) {
			msg->err_pos = ctx.line + ctx.val - req->data;
			goto return_bad_req;
		}

		txn->flags |= TX_REQ_CNT_LEN | TX_REQ_XFER_LEN;
		msg->body_len = msg->chunk_len = cl;
	}


	if (!use_close_only)
		txn->flags |= TX_REQ_XFER_LEN;


	req->analysers &= ~an_bit;
	req->analyse_exp = TICK_ETERNITY;
	return 1;

 return_bad_req:

	if (unlikely(msg->msg_state == HTTP_MSG_ERROR) || msg->err_pos >= 0) {


		http_capture_bad_message(&s->fe->invalid_req, s, req, msg, msg->msg_state, s->fe);
	}

	txn->req.msg_state = HTTP_MSG_ERROR;
	txn->status = 400;
	stream_int_retnclose(req->prod, error_message(s, HTTP_ERR_400));

	s->fe->counters.failed_req++;
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
