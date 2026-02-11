test_list_status_currentsong(struct mpd_connection *conn)
{
	struct mpd_status *status;
	const struct mpd_song *song;
	struct mpd_entity *entity;

	mpd_command_list_begin(conn, true);
	mpd_send_status(conn);
	mpd_send_current_song(conn);
	mpd_command_list_end(conn);

	CHECK_CONNECTION(conn);

	status = mpd_recv_status(conn);
	if (!status) {
		LOG_ERROR("%s", mpd_connection_get_error_message(conn));
		return -1;
	}
	if (mpd_status_get_error(status)) {
		LOG_WARNING("status error: %s", mpd_status_get_error(status));
	}

	print_status(status);
	mpd_status_free(status);

	mpd_response_next(conn);

	entity = mpd_recv_entity(conn);
	if (entity) {
		if (mpd_entity_get_type(entity) != MPD_ENTITY_TYPE_SONG) {
			LOG_ERROR("entity doesn't have the expected type (song)i :%d",
				  mpd_entity_get_type(entity));
			mpd_entity_free(entity);
			return -1;
		}

		song = mpd_entity_get_song(entity);

		print_song(song);

		mpd_entity_free(entity);
	}

	mpd_response_finish(conn);
	CHECK_CONNECTION(conn);

	return 0;
}
