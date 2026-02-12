bool release_server(PgSocket *server)
{
	PgPool *pool = server->pool;
	SocketState newstate = SV_IDLE;

	Assert(server->ready);


	switch (server->state) {
	case SV_ACTIVE:
		server->link->link = NULL;
		server->link = NULL;

		if (*cf_server_reset_query)

			newstate = SV_TESTED;
		else if (cf_server_check_delay == 0 && *cf_server_check_query)


			newstate = SV_USED;
	case SV_USED:
	case SV_TESTED:
		break;
	case SV_LOGIN:
		pool->last_connect_failed = 0;
		break;
	default:
		fatal("bad server state in release_server (%d)", server->state);
	}


	if (server->state != SV_LOGIN && life_over(server)) {
		disconnect_server(server, true, "server_lifetime");
		pool->last_lifetime_disconnect = get_cached_time();
		return false;
	}


	if (server->close_needed) {
		disconnect_server(server, true, "close_needed");
		return false;
	}

	Assert(server->link == NULL);
	slog_noise(server, "release_server: new state=%d", newstate);
	change_server_state(server, newstate);

	if (newstate == SV_IDLE)

		return reuse_on_release(server);
	else if (newstate == SV_TESTED)
		return reset_on_release(server);

	return true;
}
