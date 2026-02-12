HTTP1_Complete(struct http_conn *htc)
{
	char *p;
	enum htc_status_e retval;

	CHECK_OBJ_NOTNULL(htc, HTTP_CONN_MAGIC);

	assert(htc->rxbuf_e >= htc->rxbuf_b);
	assert(htc->rxbuf_e <= htc->ws->r);


	for (p = htc->rxbuf_b ; p < htc->rxbuf_e && vct_islws(*p); p++)
		continue;
	if (p == htc->rxbuf_e)
		return (HTC_S_EMPTY);


	retval = H2_prism_complete(htc);
	if (retval != HTC_S_JUNK)
		return (retval);


	while (1) {
		p = memchr(p, '\n', htc->rxbuf_e - p);
		if (p == NULL)
			return (HTC_S_MORE);
		if (++p == htc->rxbuf_e)
			return (HTC_S_MORE);
		if (*p == '\r' && ++p == htc->rxbuf_e)
			return (HTC_S_MORE);
		if (*p == '\n')
			break;
	}
	return (HTC_S_COMPLETE);
}
