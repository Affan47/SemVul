int http_wait_for_response(struct session *s, struct buffer *rep, int an_bit)
{
	struct http_txn *txn = &s->txn;
	struct http_msg *msg = &txn->rsp;
	struct hdr_ctx ctx;
	int use_close_only;
	int cur_idx;
	int n;

	DPRINTF(stderr,"[%u] %s: session=%p b=%p, exp(r,w)=%u,%u bf=%08x bl=%d analysers=%02x\n",
		now_ms, __FUNCTION__,
		s,
		rep,
		rep->rex, rep->wex,
		rep->flags,
		rep->l,
		rep->analysers);


	if (rep->l && msg->msg_state < HTTP_MSG_ERROR) {
		if (unlikely((rep->flags & BF_FULL) ||
			     rep->r < rep->lr ||
			     rep->r > rep->data + rep->size - global.tune.maxrewrite)) {
			if (rep->send_max) {

				if (rep->flags & (BF_SHUTW|BF_SHUTW_NOW|BF_WRITE_ERROR|BF_WRITE_TIMEOUT))
					goto abort_response;
				buffer_dont_close(rep);
				rep->flags |= BF_READ_DONTWAIT;
				return 0;
			}
			if (rep->l <= rep->size - global.tune.maxrewrite)
				http_buffer_heavy_realign(rep, msg);
		}

		if (likely(rep->lr < rep->r))
			http_msg_analyzer(rep, msg, &txn->hdr_idx);
	}


	if (unlikely((global.mode & MODE_DEBUG) &&
		     (!(global.mode & MODE_QUIET) || (global.mode & MODE_VERBOSE)) &&
		     msg->sol &&
		     (msg->msg_state >= HTTP_MSG_BODY || msg->msg_state == HTTP_MSG_ERROR))) {
		char *eol, *sol;

		sol = rep->data + msg->som;
		eol = sol + msg->sl.st.l;
		debug_hdr("srvrep", s, sol, eol);

		sol += hdr_idx_first_pos(&txn->hdr_idx);
		cur_idx = hdr_idx_first_idx(&txn->hdr_idx);

		while (cur_idx) {
			eol = sol + txn->hdr_idx.v[cur_idx].len;
			debug_hdr("srvhdr", s, sol, eol);
			sol = eol + txn->hdr_idx.v[cur_idx].cr + 1;
			cur_idx = txn->hdr_idx.v[cur_idx].next;
		}
	}


	if (unlikely(msg->msg_state < HTTP_MSG_BODY)) {

		if (unlikely(msg->msg_state == HTTP_MSG_ERROR)) {


		hdr_response_bad:
			if (msg->msg_state == HTTP_MSG_ERROR || msg->err_pos >= 0)
				http_capture_bad_message(&s->be->invalid_rep, s, rep, msg, msg->msg_state, s->fe);

			s->be->counters.failed_resp++;
			if (s->srv) {
				s->srv->counters.failed_resp++;
				health_adjust(s->srv, HANA_STATUS_HTTP_HDRRSP);
			}
		abort_response:
			buffer_auto_close(rep);
			rep->analysers = 0;
			txn->status = 502;
			rep->prod->flags |= SI_FL_NOLINGER;
			buffer_ignore(rep, rep->l - rep->send_max);
			stream_int_retnclose(rep->cons, error_message(s, HTTP_ERR_502));

			if (!(s->flags & SN_ERR_MASK))
				s->flags |= SN_ERR_PRXCOND;
			if (!(s->flags & SN_FINST_MASK))
				s->flags |= SN_FINST_H;

			return 0;
		}


		else if (rep->flags & BF_FULL) {
			if (msg->err_pos < 0)
				msg->err_pos = rep->l;
			goto hdr_response_bad;
		}


		else if (rep->flags & BF_READ_ERROR) {
			if (msg->err_pos >= 0)
				http_capture_bad_message(&s->be->invalid_rep, s, rep, msg, msg->msg_state, s->fe);

			s->be->counters.failed_resp++;
			if (s->srv) {
				s->srv->counters.failed_resp++;
				health_adjust(s->srv, HANA_STATUS_HTTP_READ_ERROR);
			}

			buffer_auto_close(rep);
			rep->analysers = 0;
			txn->status = 502;
			rep->prod->flags |= SI_FL_NOLINGER;
			buffer_ignore(rep, rep->l - rep->send_max);
			stream_int_retnclose(rep->cons, error_message(s, HTTP_ERR_502));

			if (!(s->flags & SN_ERR_MASK))
				s->flags |= SN_ERR_SRVCL;
			if (!(s->flags & SN_FINST_MASK))
				s->flags |= SN_FINST_H;
			return 0;
		}


		else if (rep->flags & BF_READ_TIMEOUT) {
			if (msg->err_pos >= 0)
				http_capture_bad_message(&s->be->invalid_rep, s, rep, msg, msg->msg_state, s->fe);

			s->be->counters.failed_resp++;
			if (s->srv) {
				s->srv->counters.failed_resp++;
				health_adjust(s->srv, HANA_STATUS_HTTP_READ_TIMEOUT);
			}

			buffer_auto_close(rep);
			rep->analysers = 0;
			txn->status = 504;
			rep->prod->flags |= SI_FL_NOLINGER;
			buffer_ignore(rep, rep->l - rep->send_max);
			stream_int_retnclose(rep->cons, error_message(s, HTTP_ERR_504));

			if (!(s->flags & SN_ERR_MASK))
				s->flags |= SN_ERR_SRVTO;
			if (!(s->flags & SN_FINST_MASK))
				s->flags |= SN_FINST_H;
			return 0;
		}


		else if ((rep->flags & BF_SHUTR) && ((s->req->flags & (BF_SHUTR|BF_SHUTW)) == (BF_SHUTR|BF_SHUTW))) {
			s->fe->counters.cli_aborts++;
			if (s->fe != s->be)
				s->be->counters.cli_aborts++;
			if (s->srv)
				s->srv->counters.cli_aborts++;

			buffer_auto_close(rep);
			rep->analysers = 0;
			txn->status = 400;
			buffer_ignore(rep, rep->l - rep->send_max);
			stream_int_retnclose(rep->cons, error_message(s, HTTP_ERR_400));

			if (!(s->flags & SN_ERR_MASK))
				s->flags |= SN_ERR_CLICL;
			if (!(s->flags & SN_FINST_MASK))
				s->flags |= SN_FINST_H;

			return 0;
		}


		else if (rep->flags & BF_SHUTR) {
			if (msg->msg_state >= HTTP_MSG_RPVER || msg->err_pos >= 0)
				http_capture_bad_message(&s->be->invalid_rep, s, rep, msg, msg->msg_state, s->fe);

			s->be->counters.failed_resp++;
			if (s->srv) {
				s->srv->counters.failed_resp++;
				health_adjust(s->srv, HANA_STATUS_HTTP_BROKEN_PIPE);
			}

			buffer_auto_close(rep);
			rep->analysers = 0;
			txn->status = 502;
			rep->prod->flags |= SI_FL_NOLINGER;
			buffer_ignore(rep, rep->l - rep->send_max);
			stream_int_retnclose(rep->cons, error_message(s, HTTP_ERR_502));

			if (!(s->flags & SN_ERR_MASK))
				s->flags |= SN_ERR_SRVCL;
			if (!(s->flags & SN_FINST_MASK))
				s->flags |= SN_FINST_H;
			return 0;
		}


		else if (rep->flags & BF_WRITE_ERROR) {
			if (msg->err_pos >= 0)
				http_capture_bad_message(&s->be->invalid_rep, s, rep, msg, msg->msg_state, s->fe);

			s->be->counters.failed_resp++;
			rep->analysers = 0;
			buffer_auto_close(rep);

			if (!(s->flags & SN_ERR_MASK))
				s->flags |= SN_ERR_CLICL;
			if (!(s->flags & SN_FINST_MASK))
				s->flags |= SN_FINST_H;


			return 0;
		}

		buffer_dont_close(rep);
		return 0;
	}


	if (unlikely(msg->err_pos >= 0))
		http_capture_bad_message(&s->be->invalid_rep, s, rep, msg, msg->msg_state, s->fe);


	n = msg->sol[msg->sl.st.c] - '0';
	if (n < 1 || n > 5)
		n = 0;
	if (s->srv)
		s->srv->counters.p.http.rsp[n]++;


	if ((msg->sl.st.v_l == 8) &&
	    ((msg->sol[5] > '1') ||
	     ((msg->sol[5] == '1') &&
	      (msg->sol[7] >= '1'))))
		txn->flags |= TX_RES_VER_11;


	txn->flags &= ~(TX_HDR_CONN_PRS|TX_HDR_CONN_CLO|TX_HDR_CONN_KAL|TX_CON_CLO_SET|TX_CON_KAL_SET);


	txn->flags &= ~TX_RES_XFER_LEN;

	txn->status = strl2ui(msg->sol + msg->sl.st.c, msg->sl.st.c_l);


	if (s->srv) {
		if (txn->status >= 100 && (txn->status < 500 || txn->status == 501 || txn->status == 505))
			health_adjust(s->srv, HANA_STATUS_HTTP_OK);
		else
			health_adjust(s->srv, HANA_STATUS_HTTP_STS);
	}


	switch (txn->status) {
	case 200:
	case 203:
	case 206:
	case 300:
	case 301:
	case 410:


		if (likely(txn->meth != HTTP_METH_POST) &&
		    ((s->be->options & PR_O_CHK_CACHE) || (s->be->ck_opts & PR_CK_NOC)))
			txn->flags |= TX_CACHEABLE | TX_CACHE_COOK;
		break;
	default:
		break;
	}


	s->logs.logwait &= ~LW_RESP;
	if (unlikely((s->logs.logwait & LW_RSPHDR) && txn->rsp.cap))
		capture_headers(msg->sol, &txn->hdr_idx,
				txn->rsp.cap, s->fe->rsp_cap);


	if (txn->meth == HTTP_METH_HEAD ||
	    (txn->status >= 100 && txn->status < 200) ||
	    txn->status == 204 || txn->status == 304) {
		txn->flags |= TX_RES_XFER_LEN;
		goto skip_content_length;
	}

	use_close_only = 0;
	ctx.idx = 0;
	while ((txn->flags & TX_RES_VER_11) &&
	       http_find_header2("Transfer-Encoding", 17, msg->sol, &txn->hdr_idx, &ctx)) {
		if (ctx.vlen == 7 && strncasecmp(ctx.line + ctx.val, "chunked", 7) == 0)
			txn->flags |= (TX_RES_TE_CHNK | TX_RES_XFER_LEN);
		else if (txn->flags & TX_RES_TE_CHNK) {

			use_close_only = 1;
			txn->flags &= ~(TX_RES_TE_CHNK | TX_RES_XFER_LEN);
			break;
		}
	}


	ctx.idx = 0;
	while (!(txn->flags & TX_RES_TE_CHNK) && !use_close_only &&
	       http_find_header2("Content-Length", 14, msg->sol, &txn->hdr_idx, &ctx)) {
		signed long long cl;

		if (!ctx.vlen) {
			msg->err_pos = ctx.line + ctx.val - rep->data;
			goto hdr_response_bad;
		}

		if (strl2llrc(ctx.line + ctx.val, ctx.vlen, &cl)) {
			msg->err_pos = ctx.line + ctx.val - rep->data;
			goto hdr_response_bad;
		}

		if (cl < 0) {
			msg->err_pos = ctx.line + ctx.val - rep->data;
			goto hdr_response_bad;
		}

		if ((txn->flags & TX_RES_CNT_LEN) && (msg->chunk_len != cl)) {
			msg->err_pos = ctx.line + ctx.val - rep->data;
			goto hdr_response_bad;
		}

		txn->flags |= TX_RES_CNT_LEN | TX_RES_XFER_LEN;
		msg->body_len = msg->chunk_len = cl;
	}


skip_content_length:


	rep->analysers &= ~an_bit;
	rep->analyse_exp = TICK_ETERNITY;
	buffer_auto_close(rep);
	return 1;
}
