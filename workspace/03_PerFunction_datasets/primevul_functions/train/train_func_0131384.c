int apply_filter_to_req_line(struct session *t, struct channel *req, struct hdr_exp *exp)
{
	char term;
	char *cur_ptr, *cur_end;
	int done;
	struct http_txn *txn = &t->txn;
	int delta;

	if (unlikely(txn->flags & (TX_CLDENY | TX_CLTARPIT)))
		return 1;
	else if (unlikely(txn->flags & TX_CLALLOW) &&
		 (exp->action == ACT_ALLOW ||
		  exp->action == ACT_DENY ||
		  exp->action == ACT_TARPIT))
		return 0;
	else if (exp->action == ACT_REMOVE)
		return 0;

	done = 0;

	cur_ptr = req->buf->p;
	cur_end = cur_ptr + txn->req.sl.rq.l;


	term = *cur_end;
	*cur_end = '\0';

	if (regexec(exp->preg, cur_ptr, MAX_MATCH, pmatch, 0) == 0) {
		switch (exp->action) {
		case ACT_SETBE:


			if (t->be != t->fe)
				break;


			session_set_backend(t, (struct proxy *)exp->replace);
			done = 1;
			break;

		case ACT_ALLOW:
			txn->flags |= TX_CLALLOW;
			done = 1;
			break;

		case ACT_DENY:
			txn->flags |= TX_CLDENY;

			t->fe->fe_counters.denied_req++;
			if (t->fe != t->be)
				t->be->be_counters.denied_req++;
			if (t->listener->counters)
				t->listener->counters->denied_req++;

			done = 1;
			break;

		case ACT_TARPIT:
			txn->flags |= TX_CLTARPIT;

			t->fe->fe_counters.denied_req++;
			if (t->fe != t->be)
				t->be->be_counters.denied_req++;
			if (t->listener->counters)
				t->listener->counters->denied_req++;

			done = 1;
			break;

		case ACT_REPLACE:
			*cur_end = term;
			trash.len = exp_replace(trash.str, cur_ptr, exp->replace, pmatch);
			delta = buffer_replace2(req->buf, cur_ptr, cur_end, trash.str, trash.len);


			http_msg_move_end(&txn->req, delta);
			cur_end += delta;
			cur_end = (char *)http_parse_reqline(&txn->req,
							     HTTP_MSG_RQMETH,
							     cur_ptr, cur_end + 1,
							     NULL, NULL);
			if (unlikely(!cur_end))
				return -1;


			txn->meth = find_http_meth(cur_ptr, txn->req.sl.rq.m_l);
			hdr_idx_set_start(&txn->hdr_idx, txn->req.sl.rq.l, *cur_end == '\r');

			return 1;
		}
	}
	*cur_end = term;
	return done;
}
