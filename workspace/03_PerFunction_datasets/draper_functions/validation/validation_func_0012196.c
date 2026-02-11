download_can_ignore(struct download *d)
{
	filesize_t remain;
	uint speed_avg;

	download_check(d);

	g_assert(d->chunk.end >= d->pos);
	g_assert(d->socket);
	g_assert(d->rx);
	g_assert(d->buffers);

	if (d->status == GTA_DL_IGNORING)
		return TRUE;

	remain = d->chunk.end - d->pos;


	if (
		SOCK_CONN_INCOMING == d->socket->direction &&
		download_has_pending_on_server(d, FALSE)
	) {
		if (GNET_PROPERTY(download_debug)) {
			uint count = server_list_length(d->server, DL_LIST_WAITING);
			g_debug("download \"%s\" has incoming connection from %s "
				"and %u waiting file%s on that server -- will sink %s bytes",
				download_basename(d), download_host_info(d),
				count, 1 == count ? "" : "s", uint64_to_string(remain));
		}

		goto sink_data;
	}


	speed_avg = download_speed_avg(d);

	if (speed_avg && remain / speed_avg > DOWNLOAD_MAX_IGN_TIME)
		goto refused;

	if (remain > DOWNLOAD_MAX_IGN_DATA)
		goto refused;

sink_data:


	(void) rx_replace_data_ind(d->rx, download_ignore_data_ind);
	download_silent_flush(d);
	download_set_status(d, GTA_DL_IGNORING);

	if (GNET_PROPERTY(download_debug) > 1)
		g_debug("will be ignoring next %s bytes of data for \"%s\"",
			uint64_to_string(remain), download_basename(d));

	return TRUE;

refused:
	gnet_stats_inc_general(GNR_IGNORING_REFUSED);
	return FALSE;
}
