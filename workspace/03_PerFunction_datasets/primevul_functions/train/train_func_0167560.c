int http_request_forward_body(struct session *s, struct buffer *req, int an_bit)
{
	struct http_txn *txn = &s->txn;
	struct http_msg *msg = &s->txn.req;

	if (unlikely(msg->msg_state < HTTP_MSG_BODY))
		return 0;

	if ((req->flags & (BF_READ_ERROR|BF_READ_TIMEOUT|BF_WRITE_ERROR|BF_WRITE_TIMEOUT)) ||
	    ((req->flags & BF_SHUTW) && (req->to_forward || req->send_max))) {

		buffer_ignore(req, req->l - req->send_max);
		buffer_auto_read(req);
		buffer_auto_close(req);
		req->analysers &= ~an_bit;
		return 1;
	}

	buffer_dont_close(req);


	if (msg->msg_state < HTTP_MSG_CHUNK_SIZE) {


		req->lr = req->data + msg->sov;
		if (txn->flags & TX_REQ_TE_CHNK)
			msg->msg_state = HTTP_MSG_CHUNK_SIZE;
		else {
			msg->msg_state = HTTP_MSG_DATA;
		}
	}

	while (1) {
		int bytes;

		http_silent_debug(__LINE__, s);

		bytes = msg->sov - msg->som;
		if (msg->chunk_len || bytes) {
			msg->som = msg->sov;
			if (likely(bytes < 0))
				bytes += req->size;
			msg->chunk_len += (unsigned int)bytes;
			msg->chunk_len -= buffer_forward(req, msg->chunk_len);
		}

		if (msg->msg_state == HTTP_MSG_DATA) {

			if (req->to_forward)
				goto missing_data;


			if (txn->flags & TX_REQ_TE_CHNK)
				msg->msg_state = HTTP_MSG_DATA_CRLF;
			else
				msg->msg_state = HTTP_MSG_DONE;
		}
		else if (msg->msg_state == HTTP_MSG_CHUNK_SIZE) {


			int ret = http_parse_chunk_size(req, msg);

			if (!ret)
				goto missing_data;
			else if (ret < 0) {
				if (msg->err_pos >= 0)
					http_capture_bad_message(&s->fe->invalid_req, s, req, msg, HTTP_MSG_CHUNK_SIZE, s->be);
				goto return_bad_req;
			}

		}
		else if (msg->msg_state == HTTP_MSG_DATA_CRLF) {

			int ret;

			req->lr = req->w + req->send_max;
			if (req->lr >= req->data + req->size)
				req->lr -= req->size;

			ret = http_skip_chunk_crlf(req, msg);

			if (ret == 0)
				goto missing_data;
			else if (ret < 0) {
				if (msg->err_pos >= 0)
					http_capture_bad_message(&s->fe->invalid_req, s, req, msg, HTTP_MSG_DATA_CRLF, s->be);
				goto return_bad_req;
			}

		}
		else if (msg->msg_state == HTTP_MSG_TRAILERS) {
			int ret = http_forward_trailers(req, msg);

			if (ret == 0)
				goto missing_data;
			else if (ret < 0) {
				if (msg->err_pos >= 0)
					http_capture_bad_message(&s->fe->invalid_req, s, req, msg, HTTP_MSG_TRAILERS, s->be);
				goto return_bad_req;
			}

		}
		else {
			int old_state = msg->msg_state;


			if (http_resync_states(s)) {


				if (unlikely(msg->msg_state == HTTP_MSG_ERROR)) {
					if (req->flags & BF_SHUTW) {


						goto aborted_xfer;
					}
					if (msg->err_pos >= 0)
						http_capture_bad_message(&s->fe->invalid_req, s, req, msg, old_state, s->be);
					goto return_bad_req;
				}
				return 1;
			}


			if (s->be->options & PR_O_ABRT_CLOSE) {
				buffer_auto_read(req);
				buffer_auto_close(req);
			}
			else if (s->txn.meth == HTTP_METH_POST) {


				buffer_auto_read(req);
			}

			return 0;
		}
	}

 missing_data:

	if (req->flags & BF_SHUTR) {
		if (!(s->flags & SN_ERR_MASK))
			s->flags |= SN_ERR_CLICL;
		if (!(s->flags & SN_FINST_MASK)) {
			if (txn->rsp.msg_state < HTTP_MSG_ERROR)
				s->flags |= SN_FINST_H;
			else
				s->flags |= SN_FINST_D;
		}

		s->fe->counters.cli_aborts++;
		if (s->fe != s->be)
			s->be->counters.cli_aborts++;
		if (s->srv)
			s->srv->counters.cli_aborts++;

		goto return_bad_req_stats_ok;
	}


	if (req->flags & BF_SHUTW)
		goto aborted_xfer;


	if (txn->flags & TX_REQ_TE_CHNK)
		req->flags |= BF_EXPECT_MORE;

	http_silent_debug(__LINE__, s);
	return 0;

 return_bad_req:
	s->fe->counters.failed_req++;
	if (s->listener->counters)
		s->listener->counters->failed_req++;
 return_bad_req_stats_ok:
	txn->req.msg_state = HTTP_MSG_ERROR;
	if (txn->status) {

		stream_int_retnclose(req->prod, NULL);
	} else {
		txn->status = 400;
		stream_int_retnclose(req->prod, error_message(s, HTTP_ERR_400));
	}
	req->analysers = 0;
	s->rep->analysers = 0;

	if (!(s->flags & SN_ERR_MASK))
		s->flags |= SN_ERR_PRXCOND;
	if (!(s->flags & SN_FINST_MASK)) {
		if (txn->rsp.msg_state < HTTP_MSG_ERROR)
			s->flags |= SN_FINST_H;
		else
			s->flags |= SN_FINST_D;
	}
	return 0;

 aborted_xfer:
	txn->req.msg_state = HTTP_MSG_ERROR;
	if (txn->status) {

		stream_int_retnclose(req->prod, NULL);
	} else {
		txn->status = 502;
		stream_int_retnclose(req->prod, error_message(s, HTTP_ERR_502));
	}
	req->analysers = 0;
	s->rep->analysers = 0;

	s->fe->counters.srv_aborts++;
	if (s->fe != s->be)
		s->be->counters.srv_aborts++;
	if (s->srv)
		s->srv->counters.srv_aborts++;

	if (!(s->flags & SN_ERR_MASK))
		s->flags |= SN_ERR_SRVCL;
	if (!(s->flags & SN_FINST_MASK)) {
		if (txn->rsp.msg_state < HTTP_MSG_ERROR)
			s->flags |= SN_FINST_H;
		else
			s->flags |= SN_FINST_D;
	}
	return 0;
}
