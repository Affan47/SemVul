http_put_cb(struct evhttp_request *req, void *arg)
{
	struct evbuffer *evb;
	event_debug(("%s: called\n", __func__));


	if (evhttp_request_get_command(req) != EVHTTP_REQ_PUT) {
		fprintf(stdout, "FAILED (put type)\n");
		exit(1);
	}

	if (evbuffer_get_length(evhttp_request_get_input_buffer(req)) != strlen(PUT_DATA)) {
		fprintf(stdout, "FAILED (length: %lu vs %lu)\n",
		    (unsigned long)evbuffer_get_length(evhttp_request_get_input_buffer(req)), (unsigned long)strlen(PUT_DATA));
		exit(1);
	}

	if (evbuffer_datacmp(evhttp_request_get_input_buffer(req), PUT_DATA) != 0) {
		fprintf(stdout, "FAILED (data)\n");
		fprintf(stdout, "Got :%s\n", evbuffer_pullup(evhttp_request_get_input_buffer(req),-1));
		fprintf(stdout, "Want:%s\n", PUT_DATA);
		exit(1);
	}

	evb = evbuffer_new();
	evbuffer_add_printf(evb, "That ain't funny");

	evhttp_send_reply(req, HTTP_OK, "Everything is great", evb);

	evbuffer_free(evb);
}
