static void bgp_write_notify(struct peer *peer)
{
	int ret, val;
	uint8_t type;
	struct stream *s;


	s = stream_fifo_pop(peer->obuf);

	if (!s)
		return;

	assert(stream_get_endp(s) >= BGP_HEADER_SIZE);


	ret = write(peer->fd, STREAM_DATA(s), stream_get_endp(s));


	if (ret <= 0) {
		stream_free(s);
		BGP_EVENT_ADD(peer, TCP_fatal_error);
		return;
	}


	val = 1;
	(void)setsockopt(peer->fd, IPPROTO_TCP, TCP_NODELAY, (char *)&val,
			 sizeof(val));


	stream_set_getp(s, BGP_MARKER_SIZE + 2);
	type = stream_getc(s);

	assert(type == BGP_MSG_NOTIFY);


	atomic_fetch_add_explicit(&peer->notify_out, 1, memory_order_relaxed);


	peer->v_start *= 2;


	if (peer->v_start >= (60 * 2))
		peer->v_start = (60 * 2);


	BGP_EVENT_ADD(peer, BGP_Stop);

	stream_free(s);
}
