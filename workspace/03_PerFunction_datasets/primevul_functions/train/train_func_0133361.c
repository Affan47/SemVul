static void http_end_request(struct stream *s)
{
	struct channel *chn = &s->req;
	struct http_txn *txn = s->txn;

	DBG_TRACE_ENTER(STRM_EV_HTTP_ANA, s, txn);

	if (unlikely(txn->req.msg_state == HTTP_MSG_ERROR ||
		     txn->rsp.msg_state == HTTP_MSG_ERROR)) {
		channel_abort(chn);
		channel_htx_truncate(chn, htxbuf(&chn->buf));
		goto end;
	}

	if (unlikely(txn->req.msg_state < HTTP_MSG_DONE)) {
		DBG_TRACE_DEVEL("waiting end of the request", STRM_EV_HTTP_ANA, s, txn);
		return;
	}

	if (txn->req.msg_state == HTTP_MSG_DONE) {


		if (!(s->be->options & PR_O_ABRT_CLOSE) && txn->meth != HTTP_METH_POST)
			channel_dont_read(chn);


		s->si[1].flags |= SI_FL_NOHALF;


		chn->flags |= CF_NEVER_WAIT;

		if (txn->rsp.msg_state < HTTP_MSG_DONE) {


			DBG_TRACE_DEVEL("waiting end of the response", STRM_EV_HTTP_ANA, s, txn);
			return;
		}


		if (txn->flags & TX_CON_WANT_TUN) {


			channel_auto_read(chn);
			if (b_data(&chn->buf)) {
				DBG_TRACE_DEVEL("waiting to flush the request", STRM_EV_HTTP_ANA, s, txn);
				return;
			}
			txn->req.msg_state = HTTP_MSG_TUNNEL;
		}
		else {


			if (!(txn->rsp.flags & HTTP_MSGF_XFER_LEN) &&
			    txn->rsp.msg_state != HTTP_MSG_CLOSED)
				goto check_channel_flags;

			if (!(chn->flags & (CF_SHUTW|CF_SHUTW_NOW))) {
				channel_shutr_now(chn);
				channel_shutw_now(chn);
			}
		}
		goto check_channel_flags;
	}

	if (txn->req.msg_state == HTTP_MSG_CLOSING) {
	  http_msg_closing:


		if (channel_is_empty(chn)) {
			txn->req.msg_state = HTTP_MSG_CLOSED;
			goto http_msg_closed;
		}
		else if (chn->flags & CF_SHUTW) {
			txn->req.msg_state = HTTP_MSG_ERROR;
			goto end;
		}
		DBG_TRACE_LEAVE(STRM_EV_HTTP_ANA, s, txn);
		return;
	}

	if (txn->req.msg_state == HTTP_MSG_CLOSED) {
	  http_msg_closed:

		if (txn->rsp.flags & HTTP_MSGF_XFER_LEN)
			s->si[1].flags |= SI_FL_NOLINGER;

		if (!(s->be->options & PR_O_ABRT_CLOSE))
			channel_dont_read(chn);
		goto end;
	}

  check_channel_flags:

	if (chn->flags & (CF_SHUTW|CF_SHUTW_NOW)) {

		txn->req.msg_state = HTTP_MSG_CLOSING;
		goto http_msg_closing;
	}

  end:
	chn->analysers &= AN_REQ_FLT_END;
	if (txn->req.msg_state == HTTP_MSG_TUNNEL) {
		chn->flags |= CF_NEVER_WAIT;
		if (HAS_REQ_DATA_FILTERS(s))
			chn->analysers |= AN_REQ_FLT_XFER_DATA;
	}
	channel_auto_close(chn);
	channel_auto_read(chn);
	DBG_TRACE_LEAVE(STRM_EV_HTTP_ANA, s, txn);
}
