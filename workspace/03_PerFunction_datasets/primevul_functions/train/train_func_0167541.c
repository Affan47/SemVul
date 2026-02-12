int http_resync_states(struct session *s)
{
	struct http_txn *txn = &s->txn;
	int old_req_state = txn->req.msg_state;
	int old_res_state = txn->rsp.msg_state;

	http_silent_debug(__LINE__, s);
	http_sync_req_state(s);
	while (1) {
		http_silent_debug(__LINE__, s);
		if (!http_sync_res_state(s))
			break;
		http_silent_debug(__LINE__, s);
		if (!http_sync_req_state(s))
			break;
	}
	http_silent_debug(__LINE__, s);


	if (txn->req.msg_state == HTTP_MSG_TUNNEL ||
	    txn->rsp.msg_state == HTTP_MSG_TUNNEL ||
	    (txn->req.msg_state == HTTP_MSG_CLOSED &&
	     txn->rsp.msg_state == HTTP_MSG_CLOSED)) {
		s->req->analysers = 0;
		buffer_auto_close(s->req);
		buffer_auto_read(s->req);
		s->rep->analysers = 0;
		buffer_auto_close(s->rep);
		buffer_auto_read(s->rep);
	}
	else if ((txn->req.msg_state >= HTTP_MSG_DONE &&
		  (txn->rsp.msg_state == HTTP_MSG_CLOSED || (s->rep->flags & BF_SHUTW))) ||
		 txn->rsp.msg_state == HTTP_MSG_ERROR ||
		 txn->req.msg_state == HTTP_MSG_ERROR) {
		s->rep->analysers = 0;
		buffer_auto_close(s->rep);
		buffer_auto_read(s->rep);
		s->req->analysers = 0;
		buffer_abort(s->req);
		buffer_auto_close(s->req);
		buffer_auto_read(s->req);
		buffer_ignore(s->req, s->req->l - s->req->send_max);
	}
	else if (txn->req.msg_state == HTTP_MSG_CLOSED &&
		 txn->rsp.msg_state == HTTP_MSG_DONE &&
		 ((txn->flags & TX_CON_WANT_MSK) == TX_CON_WANT_SCL)) {


		http_end_txn_clean_session(s);
	}

	http_silent_debug(__LINE__, s);
	return txn->req.msg_state != old_req_state ||
		txn->rsp.msg_state != old_res_state;
}
