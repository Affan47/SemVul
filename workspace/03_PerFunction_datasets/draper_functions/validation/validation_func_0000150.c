http_request_done(struct evhttp_request *req, void *arg)
{
	const char *what = arg;

	if (evhttp_request_get_response_code(req) != HTTP_OK) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	if (evhttp_find_header(evhttp_request_get_input_headers(req), "Content-Type") == NULL) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	if (evbuffer_get_length(evhttp_request_get_input_buffer(req)) != strlen(what)) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	if (evbuffer_datacmp(evhttp_request_get_input_buffer(req), what) != 0) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	test_ok = 1;
	EVUTIL_ASSERT(exit_base);
	event_base_loopexit(exit_base, NULL);
}
