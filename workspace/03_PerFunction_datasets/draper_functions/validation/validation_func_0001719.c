evhttp_set_cb(struct evhttp *http, const char *uri,
    void (*cb)(struct evhttp_request *, void *), void *cbarg)
{
	struct evhttp_cb *http_cb;

	TAILQ_FOREACH(http_cb, &http->callbacks, next) {
		if (strcmp(http_cb->what, uri) == 0)
			return (-1);
	}

	if ((http_cb = mm_calloc(1, sizeof(struct evhttp_cb))) == NULL) {
		event_warn("%s: calloc", __func__);
		return (-2);
	}

	http_cb->what = mm_strdup(uri);
	if (http_cb->what == NULL) {
		event_warn("%s: strdup", __func__);
		mm_free(http_cb);
		return (-3);
	}
	http_cb->cb = cb;
	http_cb->cbarg = cbarg;

	TAILQ_INSERT_TAIL(&http->callbacks, http_cb, next);

	return (0);
}
