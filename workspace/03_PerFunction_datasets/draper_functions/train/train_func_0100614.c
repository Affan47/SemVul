handle_reset(struct httpsqs* h, struct evhttp_request *req, struct sqs_queue_status *qs, struct evkeyvalq *args) {
	if (httpsqs_reset(h, qs)) {
		qs->total_info++;

		struct evbuffer *buf = evbuffer_new();
		evbuffer_add_printf(buf, "%s", "{'success':true}");
		evhttp_send_reply(req, HTTP_OK, "OK", buf);
		evbuffer_free(buf);
	} else {
		send_error(req, 500, "Internal Server Error", "Could not reset queue");
	}
}
