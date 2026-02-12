acl_fetch_proto_http(struct proxy *px, struct session *s, void *l7, int dir,
		     struct acl_expr *expr, struct acl_test *test)
{
	struct buffer *req = s->req;
	struct http_txn *txn = &s->txn;
	struct http_msg *msg = &txn->req;


	if (!s || !req)
		return 0;

	if (unlikely(msg->msg_state >= HTTP_MSG_BODY)) {

		test->flags |= ACL_TEST_F_SET_RES_PASS;
		return 1;
	}


	if (unlikely(req->lr > req->data &&
	    (req->r < req->lr || req->r > req->data + req->size - global.tune.maxrewrite)) &&
	    (req->l <= req->size - global.tune.maxrewrite))
		http_buffer_heavy_realign(req, msg);


	if (likely(req->lr < req->r))
		http_msg_analyzer(req, msg, &txn->hdr_idx);

	if (unlikely(msg->msg_state < HTTP_MSG_BODY)) {
		if ((msg->msg_state == HTTP_MSG_ERROR) || (req->flags & BF_FULL)) {
			test->flags |= ACL_TEST_F_SET_RES_FAIL;
			return 1;
		}

		test->flags |= ACL_TEST_F_MAY_CHANGE;
		return 0;
	}


	if (unlikely(req->lr > req->data &&
	    (req->r < req->lr || req->l > req->size - global.tune.maxrewrite ||
	     req->r > req->data + req->size - global.tune.maxrewrite))) {
		msg->msg_state = HTTP_MSG_ERROR;
		test->flags |= ACL_TEST_F_SET_RES_PASS;
		return 1;
	}

	txn->meth = find_http_meth(msg->sol, msg->sl.rq.m_l);
	if (txn->meth == HTTP_METH_GET || txn->meth == HTTP_METH_HEAD)
		s->flags |= SN_REDIRECTABLE;

	if (unlikely(msg->sl.rq.v_l == 0) && !http_upgrade_v09_to_v10(req, msg, txn)) {
		test->flags |= ACL_TEST_F_SET_RES_FAIL;
		return 1;
	}

	test->flags |= ACL_TEST_F_SET_RES_PASS;
	return 1;
}
