evrpc_request_done_closure(void *arg, enum EVRPC_HOOK_RESULT hook_res)
{
	struct evrpc_req_generic *rpc_state = arg;
	struct evhttp_request *req = rpc_state->http_req;

	if (hook_res == EVRPC_TERMINATE)
		goto error;


	if (evhttp_find_header(req->output_headers, "Content-Type") == NULL) {
		evhttp_add_header(req->output_headers,
		    "Content-Type", "application/octet-stream");
	}
	evhttp_send_reply(req, HTTP_OK, "OK", rpc_state->rpc_data);

	evrpc_reqstate_free(rpc_state);

	return;

error:
	if (rpc_state != NULL)
		evrpc_reqstate_free(rpc_state);
	evhttp_send_error(req, HTTP_SERVUNAVAIL, NULL);
	return;
}
