static int ldb_lock_backend_callback(struct ldb_request *req,
				     struct ldb_reply *ares)
{
	struct ldb_db_lock_context *lock_context;
	int ret;

	if (req->context == NULL) {


		abort();
	}
	lock_context = talloc_get_type(req->context,
				       struct ldb_db_lock_context);

	if (!ares) {
		return ldb_module_done(lock_context->req, NULL, NULL,
					LDB_ERR_OPERATIONS_ERROR);
	}
	if (ares->error != LDB_SUCCESS || ares->type == LDB_REPLY_DONE) {
		ret = ldb_module_done(lock_context->req, ares->controls,
				      ares->response, ares->error);


		TALLOC_FREE(req->context);
		return ret;
	}


	switch (ares->type) {
	case LDB_REPLY_ENTRY:
		return ldb_module_send_entry(lock_context->req, ares->message,
					     ares->controls);

	case LDB_REPLY_REFERRAL:
		return ldb_module_send_referral(lock_context->req,
						ares->referral);
	default:

		return LDB_ERR_OPERATIONS_ERROR;
	}
}
