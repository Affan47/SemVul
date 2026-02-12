int http_response_forward_body(struct session *s, struct buffer *res, int an_bit)
{
	struct http_txn *txn = &s->txn;
	struct http_msg *msg = &s->txn.rsp;
	int bytes;

	if (unlikely(msg->msg_state < HTTP_MSG_BODY))
		return 0;

	if ((res->flags & (BF_READ_ERROR|BF_READ_TIMEOUT|BF_WRITE_ERROR|BF_WRITE_TIMEOUT)) ||
	    ((res->flags & BF_SHUTW) && (res->to_forward || res->send_max)) ||
	    !s->req->analysers) {

		buffer_ignore(res, res->l - res->send_max);
		buffer_auto_read(res);
		buffer_auto_close(res);
		res->analysers &= ~an_bit;
		return 1;
	}

	buffer_dont_close(res);

	if (msg->msg_state < HTTP_MSG_CHUNK_SIZE) {


		res->lr = res->data + msg->sov;
		if (txn->flags & TX_RES_TE_CHNK)
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
				bytes += res->size;
			msg->chunk_len += (unsigned int)bytes;
			msg->chunk_len -= buffer_forward(res, msg->chunk_len);
		}


		if (msg->msg_state == HTTP_MSG_DATA) {

			if (res->to_forward)
				goto missing_data;


			if (txn->flags & TX_RES_TE_CHNK)
				msg->msg_state = HTTP_MSG_DATA_CRLF;
			else
				msg->msg_state = HTTP_MSG_DONE;
		}
		else if (msg->msg_state == HTTP_MSG_CHUNK_SIZE) {


			int ret = http_parse_chunk_size(res, msg);

			if (!ret)
				goto missing_data;
			else if (ret < 0) {
				if (msg->err_pos >= 0)
					http_capture_bad_message(&s->be->invalid_rep, s, res, msg, HTTP_MSG_CHUNK_SIZE, s->fe);
				goto return_bad_res;
			}

		}
		else if (msg->msg_state == HTTP_MSG_DATA_CRLF) {

			int ret;

			res->lr = res->w + res->send_max;
			if (res->lr >= res->data + res->size)
				res->lr -= res->size;

			ret = http_skip_chunk_crlf(res, msg);

			if (!ret)
				goto missing_data;
			else if (ret < 0) {
				if (msg->err_pos >= 0)
					http_capture_bad_message(&s->be->invalid_rep, s, res, msg, HTTP_MSG_DATA_CRLF, s->fe);
				goto return_bad_res;
			}

		}
		else if (msg->msg_state == HTTP_MSG_TRAILERS) {
			int ret = http_forward_trailers(res, msg);

			if (ret == 0)
				goto missing_data;
			else if (ret < 0) {
				if (msg->err_pos >= 0)
					http_capture_bad_message(&s->be->invalid_rep, s, res, msg, HTTP_MSG_TRAILERS, s->fe);
				goto return_bad_res;
			}

		}
		else {
			int old_state = msg->msg_state;


			if (http_resync_states(s)) {
				http_silent_debug(__LINE__, s);


				if (unlikely(msg->msg_state == HTTP_MSG_ERROR)) {
					if (res->flags & BF_SHUTW) {


						goto aborted_xfer;
					}
					if (msg->err_pos >= 0)
						http_capture_bad_message(&s->be->invalid_rep, s, res, msg, old_state, s->fe);
					goto return_bad_res;
				}
				return 1;
			}
			return 0;
		}
	}

 missing_data:

	if (res->flags & BF_SHUTW)
		goto aborted_xfer;


	if (res->flags & BF_SHUTR) {
		if ((res->flags & BF_SHUTW_NOW) || (s->req->flags & BF_SHUTR))
			goto aborted_xfer;
		if (!(s->flags & SN_ERR_MASK))
			s->flags |= SN_ERR_SRVCL;
		s->be->counters.srv_aborts++;
		if (s->srv)
			s->srv->counters.srv_aborts++;
		goto return_bad_res_stats_ok;
	}


	if (!s->req->analysers)
		goto return_bad_res;


	bytes = msg->sov - msg->som;
	if (msg->chunk_len || bytes) {
		msg->som = msg->sov;
		if (likely(bytes < 0))
			bytes += res->size;
		msg->chunk_len += (unsigned int)bytes;
		msg->chunk_len -= buffer_forward(res, msg->chunk_len);
	}


	if (txn->flags & TX_RES_TE_CHNK)
		res->flags |= BF_EXPECT_MORE;


	http_silent_debug(__LINE__, s);
	return 0;

 return_bad_res:
	s->be->counters.failed_resp++;
	if (s->srv)
		s->srv->counters.failed_resp++;

 return_bad_res_stats_ok:
	txn->rsp.msg_state = HTTP_MSG_ERROR;

	stream_int_retnclose(res->cons, NULL);
	res->analysers = 0;
	s->req->analysers = 0;
	if (s->srv)
		health_adjust(s->srv, HANA_STATUS_HTTP_HDRRSP);

	if (!(s->flags & SN_ERR_MASK))
		s->flags |= SN_ERR_PRXCOND;
	if (!(s->flags & SN_FINST_MASK))
		s->flags |= SN_FINST_D;
	return 0;

 aborted_xfer:
	txn->rsp.msg_state = HTTP_MSG_ERROR;

	stream_int_retnclose(res->cons, NULL);
	res->analysers = 0;
	s->req->analysers = 0;

	s->fe->counters.cli_aborts++;
	if (s->fe != s->be)
		s->be->counters.cli_aborts++;
	if (s->srv)
		s->srv->counters.cli_aborts++;

	if (!(s->flags & SN_ERR_MASK))
		s->flags |= SN_ERR_CLICL;
	if (!(s->flags & SN_FINST_MASK))
		s->flags |= SN_FINST_D;
	return 0;
}
