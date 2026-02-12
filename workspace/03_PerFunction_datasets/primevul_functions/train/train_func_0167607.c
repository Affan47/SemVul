int http_sync_req_state(struct session *s)
{
	struct buffer *buf = s->req;
	struct http_txn *txn = &s->txn;
	unsigned int old_flags = buf->flags;
	unsigned int old_state = txn->req.msg_state;

	http_silent_debug(__LINE__, s);
	if (unlikely(txn->req.msg_state < HTTP_MSG_BODY))
		return 0;

	if (txn->req.msg_state == HTTP_MSG_DONE) {


		if (!(s->be->options & PR_O_ABRT_CLOSE) && txn->meth != HTTP_METH_POST)
			buffer_dont_read(buf);

		if (txn->rsp.msg_state == HTTP_MSG_ERROR)
			goto wait_other_side;

		if (txn->rsp.msg_state < HTTP_MSG_DONE) {


			goto wait_other_side;
		}

		if (txn->rsp.msg_state == HTTP_MSG_TUNNEL) {

			buffer_auto_read(buf);
			txn->req.msg_state = HTTP_MSG_TUNNEL;
			buf->flags |= BF_NEVER_WAIT;
			goto wait_other_side;
		}


		if ((txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_SCL) {

			if (!(buf->flags & (BF_SHUTW|BF_SHUTW_NOW)))
				buffer_shutw_now(buf);
		}
		else if ((txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_CLO) {


			if (!(buf->flags & (BF_SHUTW|BF_SHUTW_NOW))) {
				buffer_shutr_now(buf);
				buffer_shutw_now(buf);
			}
		}
		else {


			buffer_auto_read(buf);
			txn->req.msg_state = HTTP_MSG_TUNNEL;
			buf->flags |= BF_NEVER_WAIT;
		}

		if (buf->flags & (BF_SHUTW|BF_SHUTW_NOW)) {

			buf->cons->flags |= SI_FL_NOLINGER;

			if (!(buf->flags & BF_OUT_EMPTY)) {
				txn->req.msg_state = HTTP_MSG_CLOSING;
				goto http_msg_closing;
			}
			else {
				txn->req.msg_state = HTTP_MSG_CLOSED;
				goto http_msg_closed;
			}
		}
		goto wait_other_side;
	}

	if (txn->req.msg_state == HTTP_MSG_CLOSING) {
	http_msg_closing:


		if (buf->flags & BF_OUT_EMPTY) {
			txn->req.msg_state = HTTP_MSG_CLOSED;
			goto http_msg_closed;
		}
		else if (buf->flags & BF_SHUTW) {
			txn->req.msg_state = HTTP_MSG_ERROR;
			goto wait_other_side;
		}
	}

	if (txn->req.msg_state == HTTP_MSG_CLOSED) {
	http_msg_closed:
		goto wait_other_side;
	}

 wait_other_side:
	http_silent_debug(__LINE__, s);
	return txn->req.msg_state != old_state || buf->flags != old_flags;
}
