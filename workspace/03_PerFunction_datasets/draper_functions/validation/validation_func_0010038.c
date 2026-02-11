evhttp_del_accept_socket(struct evhttp *http, struct evhttp_bound_socket *bound)
{
	TAILQ_REMOVE(&http->sockets, bound, next);
	evconnlistener_free(bound->listener);
	mm_free(bound);
}
