int http_sync_res_state(struct session *s)
{
	struct buffer *buf = s->rep;
	struct http_txn *txn = &s->txn;
	unsigned int old_flags = buf->flags;
	unsigned int old_state = txn->rsp.msg_state;

	http_silent_debug(__LINE__, s);
	if (unlikely(txn->rsp.msg_state < HTTP_MSG_BODY))
		return 0;

	if (txn->rsp.msg_state == HTTP_MSG_DONE) {


		if (txn->req.msg_state == HTTP_MSG_ERROR)
			goto wait_other_side;

		if (txn->req.msg_state < HTTP_MSG_DONE) {


			goto wait_other_side;
		}

		if (txn->req.msg_state == HTTP_MSG_TUNNEL) {

			buffer_auto_read(buf);
			txn->rsp.msg_state = HTTP_MSG_TUNNEL;
			buf->flags |= BF_NEVER_WAIT;
			goto wait_other_side;
		}


		if ((txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_SCL) {


			if (!(buf->flags & (BF_SHUTR|BF_SHUTR_NOW)))
				buffer_shutr_now(buf);
		}
		else if ((txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_CLO) {


			if (!(buf->flags & (BF_SHUTW|BF_SHUTW_NOW))) {
				buffer_shutr_now(buf);
				buffer_shutw_now(buf);
			}
		}
		else {


			buffer_auto_read(buf);
			txn->rsp.msg_state = HTTP_MSG_TUNNEL;
			buf->flags |= BF_NEVER_WAIT;
		}

		if (buf->flags & (BF_SHUTW|BF_SHUTW_NOW)) {

			if (!(buf->flags & BF_OUT_EMPTY)) {
				txn->rsp.msg_state = HTTP_MSG_CLOSING;
				goto http_msg_closing;
			}
			else {
				txn->rsp.msg_state = HTTP_MSG_CLOSED;
				goto http_msg_closed;
			}
		}
		goto wait_other_side;
	}

	if (txn->rsp.msg_state == HTTP_MSG_CLOSING) {
	http_msg_closing:


		if (buf->flags & BF_OUT_EMPTY) {
			txn->rsp.msg_state = HTTP_MSG_CLOSED;
			goto http_msg_closed;
		}
		else if (buf->flags & BF_SHUTW) {
			txn->rsp.msg_state = HTTP_MSG_ERROR;
			s->be->counters.cli_aborts++;
			if (s->srv)
				s->srv->counters.cli_aborts++;
			goto wait_other_side;
		}
	}

	if (txn->rsp.msg_state == HTTP_MSG_CLOSED) {
	http_msg_closed:

		buffer_ignore(buf, buf->l - buf->send_max);
		buffer_auto_close(buf);
		buffer_auto_read(buf);
		goto wait_other_side;
	}

 wait_other_side:
	http_silent_debug(__LINE__, s);


	if (!(buf->flags & BF_OUT_EMPTY))
		buf->flags |= BF_SEND_DONTWAIT;
	return txn->rsp.msg_state != old_state || buf->flags != old_flags;
}
