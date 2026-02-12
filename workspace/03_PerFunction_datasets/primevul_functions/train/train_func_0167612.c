void http_end_txn_clean_session(struct session *s)
{


	http_silent_debug(__LINE__, s);

	s->req->cons->flags |= SI_FL_NOLINGER;
	s->req->cons->shutr(s->req->cons);
	s->req->cons->shutw(s->req->cons);

	http_silent_debug(__LINE__, s);

	if (s->flags & SN_BE_ASSIGNED) {
		s->be->beconn--;
		if (unlikely(s->srv_conn))
			sess_change_server(s, NULL);
	}

	s->logs.t_close = tv_ms_elapsed(&s->logs.tv_accept, &now);
	session_process_counters(s);

	if (s->txn.status) {
		int n;

		n = s->txn.status / 100;
		if (n < 1 || n > 5)
			n = 0;

		if (s->fe->mode == PR_MODE_HTTP)
			s->fe->counters.fe.http.rsp[n]++;

		if ((s->flags & SN_BE_ASSIGNED) &&
		    (s->be->mode == PR_MODE_HTTP))
			s->be->counters.be.http.rsp[n]++;
	}


	s->logs.bytes_in  -= s->req->l - s->req->send_max;
	s->logs.bytes_out -= s->rep->l - s->rep->send_max;


	if (s->logs.logwait &&
	    !(s->flags & SN_MONITOR) &&
	    (!(s->fe->options & PR_O_NULLNOLOG) || s->req->total)) {
		s->do_log(s);
	}

	s->logs.accept_date = date;
	s->logs.tv_accept = now;
	tv_zero(&s->logs.tv_request);
	s->logs.t_queue = -1;
	s->logs.t_connect = -1;
	s->logs.t_data = -1;
	s->logs.t_close = 0;
	s->logs.prx_queue_size = 0;
	s->logs.srv_queue_size = 0;

	s->logs.bytes_in = s->req->total = s->req->l - s->req->send_max;
	s->logs.bytes_out = s->rep->total = s->rep->l - s->rep->send_max;

	if (s->pend_pos)
		pendconn_free(s->pend_pos);

	if (s->srv) {
		if (s->flags & SN_CURR_SESS) {
			s->flags &= ~SN_CURR_SESS;
			s->srv->cur_sess--;
		}
		if (may_dequeue_tasks(s->srv, s->be))
			process_srv_queue(s->srv);
	}

	s->srv = NULL;

	s->req->cons->state     = s->req->cons->prev_state = SI_ST_INI;
	s->req->cons->fd        = -1;
	s->req->cons->err_type  = SI_ET_NONE;
	s->req->cons->err_loc   = NULL;
	s->req->cons->exp       = TICK_ETERNITY;
	s->req->cons->flags     = SI_FL_NONE;
	s->req->flags &= ~(BF_SHUTW|BF_SHUTW_NOW|BF_AUTO_CONNECT|BF_WRITE_ERROR|BF_STREAMER|BF_STREAMER_FAST|BF_NEVER_WAIT);
	s->rep->flags &= ~(BF_SHUTR|BF_SHUTR_NOW|BF_READ_ATTACHED|BF_READ_ERROR|BF_READ_NOEXP|BF_STREAMER|BF_STREAMER_FAST|BF_WRITE_PARTIAL|BF_NEVER_WAIT);
	s->flags &= ~(SN_DIRECT|SN_ASSIGNED|SN_ADDR_SET|SN_BE_ASSIGNED|SN_FORCE_PRST|SN_IGNORE_PRST);
	s->flags &= ~(SN_CURR_SESS|SN_REDIRECTABLE);
	s->txn.meth = 0;
	http_reset_txn(s);
	s->txn.flags |= TX_NOT_FIRST | TX_WAIT_NEXT_RQ;
	if (s->be->options2 & PR_O2_INDEPSTR)
		s->req->cons->flags |= SI_FL_INDEP_STR;

	if (s->fe->options2 & PR_O2_NODELAY) {
		s->req->flags |= BF_NEVER_WAIT;
		s->rep->flags |= BF_NEVER_WAIT;
	}


	if (s->req->l > s->req->send_max) {
		if (s->rep->send_max &&
		    !(s->rep->flags & BF_FULL) &&
		    s->rep->r <= s->rep->data + s->rep->size - global.tune.maxrewrite)
			s->rep->flags |= BF_EXPECT_MORE;
	}


	buffer_auto_read(s->req);
	buffer_auto_close(s->req);
	buffer_auto_read(s->rep);
	buffer_auto_close(s->rep);


	s->req->lr = s->req->w + s->req->send_max;
	if (s->req->lr >= s->req->data + s->req->size)
		s->req->lr -= s->req->size;
	s->rep->lr = s->rep->w + s->rep->send_max;
	if (s->rep->lr >= s->rep->data + s->rep->size)
		s->rep->lr -= s->req->size;

	s->req->analysers |= s->fe->fe_req_ana;
	s->rep->analysers = 0;

	http_silent_debug(__LINE__, s);
}
