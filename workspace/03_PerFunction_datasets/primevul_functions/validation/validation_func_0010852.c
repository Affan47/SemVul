evbuffer_chain_insert(struct evbuffer *buf,
    struct evbuffer_chain *chain)
{
	ASSERT_EVBUFFER_LOCKED(buf);
	if (*buf->last_with_datap == NULL) {

		EVUTIL_ASSERT(buf->last_with_datap == &buf->first);
		EVUTIL_ASSERT(buf->first == NULL);
		buf->first = buf->last = chain;
	} else {
		struct evbuffer_chain **ch = buf->last_with_datap;

		while ((*ch) && ((*ch)->off != 0 || CHAIN_PINNED(*ch)))
			ch = &(*ch)->next;
		if (*ch == NULL) {

			buf->last->next = chain;
			if (chain->off)
				buf->last_with_datap = &buf->last->next;
		} else {

			EVUTIL_ASSERT(evbuffer_chains_all_empty(*ch));
			evbuffer_free_all_chains(*ch);
			*ch = chain;
		}
		buf->last = chain;
	}
	buf->total_len += chain->off;
}
