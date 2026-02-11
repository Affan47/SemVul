download_sink_read(void *data, int unused_source,
	inputevt_cond_t unused_cond)
{
	struct download *d = data;
	struct gnutella_socket *s;
	ssize_t r;

	(void) unused_source;
	(void) unused_cond;

	download_check(d);

	s = d->socket;
	g_assert(s);

	r = bio_read(d->bio, s->buf, s->buf_size);
	if (0 == r) {
		socket_eof(s);
		download_queue_delay(d, GNET_PROPERTY(download_retry_busy_delay),
			_("Stopped data (EOF)"));
	} else if ((ssize_t) -1 == r) {
		if (!is_temporary_error(errno)) {
			socket_eof(s);
			if (errno == ECONNRESET)
				download_queue_delay(d,
					GNET_PROPERTY(download_retry_busy_delay),
					_("Stopped data (%s)"), g_strerror(errno));
			else
				download_stop(d, GTA_DL_ERROR,
					_("Failed (Read error: %s)"), g_strerror(errno));
		}
	} else {
		s->pos = r;
		d->last_update = tm_time();

		download_sink(d);
	}
}
