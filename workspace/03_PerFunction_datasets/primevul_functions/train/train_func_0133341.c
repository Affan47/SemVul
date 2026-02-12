int http_process_request(struct stream *s, struct channel *req, int an_bit)
{
	struct session *sess = s->sess;
	struct http_txn *txn = s->txn;
	struct htx *htx;
	struct connection *cli_conn = objt_conn(strm_sess(s)->origin);

	DBG_TRACE_ENTER(STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);


	htx = htxbuf(&req->buf);


	if (s->be->cookie_name || sess->fe->capture_name)
		http_manage_client_side_cookies(s, req);


	if (!LIST_ISEMPTY(&sess->fe->format_unique_id)) {
		struct ist unique_id = stream_generate_unique_id(s, &sess->fe->format_unique_id);

		if (!isttest(unique_id)) {
			if (!(s->flags & SF_ERR_MASK))
				s->flags |= SF_ERR_RESOURCE;
			goto return_int_err;
		}


		if (isttest(sess->fe->header_unique_id) &&
		    unlikely(!http_add_header(htx, sess->fe->header_unique_id, s->unique_id)))
				goto return_int_err;
	}


	if ((sess->fe->options | s->be->options) & PR_O_FWDFOR) {
		const struct sockaddr_storage *src = si_src(&s->si[0]);
		struct http_hdr_ctx ctx = { .blk = NULL };
		struct ist hdr = ist2(s->be->fwdfor_hdr_len ? s->be->fwdfor_hdr_name : sess->fe->fwdfor_hdr_name,
				      s->be->fwdfor_hdr_len ? s->be->fwdfor_hdr_len : sess->fe->fwdfor_hdr_len);

		if (!((sess->fe->options | s->be->options) & PR_O_FF_ALWAYS) &&
		    http_find_header(htx, hdr, &ctx, 0)) {


		}
		else if (src && src->ss_family == AF_INET) {


			if (ipcmp2net(src, &sess->fe->except_xff_net) &&
			    ipcmp2net(src, &s->be->except_xff_net)) {
				unsigned char *pn = (unsigned char *)&((struct sockaddr_in *)src)->sin_addr;


				chunk_printf(&trash, "%d.%d.%d.%d", pn[0], pn[1], pn[2], pn[3]);
				if (unlikely(!http_add_header(htx, hdr, ist2(trash.area, trash.data))))
					goto return_int_err;
			}
		}
		else if (src && src->ss_family == AF_INET6) {


			if (ipcmp2net(src, &sess->fe->except_xff_net) &&
			    ipcmp2net(src, &s->be->except_xff_net)) {
				char pn[INET6_ADDRSTRLEN];

				inet_ntop(AF_INET6,
					  (const void *)&((struct sockaddr_in6 *)(src))->sin6_addr,
					  pn, sizeof(pn));


				chunk_printf(&trash, "%s", pn);
				if (unlikely(!http_add_header(htx, hdr, ist2(trash.area, trash.data))))
					goto return_int_err;
			}
		}
	}


	if ((sess->fe->options | s->be->options) & PR_O_ORGTO) {
		const struct sockaddr_storage *dst = si_dst(&s->si[0]);
		struct ist hdr = ist2(s->be->orgto_hdr_len ? s->be->orgto_hdr_name : sess->fe->orgto_hdr_name,
				      s->be->orgto_hdr_len ? s->be->orgto_hdr_len  : sess->fe->orgto_hdr_len);

		if (dst && dst->ss_family == AF_INET) {


			if (ipcmp2net(dst, &sess->fe->except_xot_net) &&
			    ipcmp2net(dst, &s->be->except_xot_net)) {
				unsigned char *pn = (unsigned char *)&((struct sockaddr_in *)dst)->sin_addr;


				chunk_printf(&trash, "%d.%d.%d.%d", pn[0], pn[1], pn[2], pn[3]);
				if (unlikely(!http_add_header(htx, hdr, ist2(trash.area, trash.data))))
					goto return_int_err;
			}
		}
		else if (dst && dst->ss_family == AF_INET6) {


			if (ipcmp2net(dst, &sess->fe->except_xot_net) &&
			    ipcmp2net(dst, &s->be->except_xot_net)) {
				char pn[INET6_ADDRSTRLEN];

				inet_ntop(AF_INET6,
					  (const void *)&((struct sockaddr_in6 *)dst)->sin6_addr,
					  pn, sizeof(pn));


				chunk_printf(&trash, "%s", pn);
				if (unlikely(!http_add_header(htx, hdr, ist2(trash.area, trash.data))))
					goto return_int_err;
			}
		}
	}


	if (HAS_FILTERS(s))
		req->analysers |= AN_REQ_FLT_HTTP_HDRS;


	if (!(s->flags & (SF_ASSIGNED|SF_DIRECT)) &&
	    s->txn->meth == HTTP_METH_POST &&
	    (s->be->lbprm.algo & BE_LB_ALGO) == BE_LB_ALGO_PH) {
		channel_dont_connect(req);
		req->analysers |= AN_REQ_HTTP_BODY;
	}

	req->analysers &= ~AN_REQ_FLT_XFER_DATA;
	req->analysers |= AN_REQ_HTTP_XFER_BODY;


	if ((sess->listener && (sess->listener->options & LI_O_NOQUICKACK)) && !(htx->flags & HTX_FL_EOM))
		conn_set_quickack(cli_conn, 1);


	req->analyse_exp = TICK_ETERNITY;
	req->analysers &= ~an_bit;

	s->logs.tv_request = now;

	DBG_TRACE_LEAVE(STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA, s, txn);
	return 1;

 return_int_err:
	txn->status = 500;
	if (!(s->flags & SF_ERR_MASK))
		s->flags |= SF_ERR_INTERNAL;
	_HA_ATOMIC_INC(&sess->fe->fe_counters.internal_errors);
	if (s->flags & SF_BE_ASSIGNED)
		_HA_ATOMIC_INC(&s->be->be_counters.internal_errors);
	if (sess->listener && sess->listener->counters)
		_HA_ATOMIC_INC(&sess->listener->counters->internal_errors);

	http_reply_and_close(s, txn->status, http_error_message(s));

	if (!(s->flags & SF_ERR_MASK))
		s->flags |= SF_ERR_PRXCOND;
	if (!(s->flags & SF_FINST_MASK))
		s->flags |= SF_FINST_R;

	DBG_TRACE_DEVEL("leaving on error",
			STRM_EV_STRM_ANA|STRM_EV_HTTP_ANA|STRM_EV_HTTP_ERR, s, txn);
	return 0;
}
