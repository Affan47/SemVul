bool find_server(PgSocket *client)
{
	PgPool *pool = client->pool;
	PgSocket *server;
	bool res;
	bool varchange = false;

	Assert(client->state == CL_ACTIVE);

	if (client->link)
		return true;


	if (cf_pause_mode == P_PAUSE) {
		server = NULL;
	} else {
		while (1) {
			server = first_socket(&pool->idle_server_list);
			if (!server)
				break;
			else if (server->close_needed)
				disconnect_server(server, true, "obsolete connection");
			else if (!server->ready)
				disconnect_server(server, true, "idle server got dirty");
			else
				break;
		}

		if (!server && !check_fast_fail(client))
			return false;

	}
	Assert(!server || server->state == SV_IDLE);


	if (server) {
		res = varcache_apply(server, client, &varchange);
		if (!res) {
			disconnect_server(server, true, "var change failed");
			server = NULL;
		}
	}


	if (server) {
		client->link = server;
		server->link = client;
		change_server_state(server, SV_ACTIVE);
		if (varchange) {
			server->setting_vars = 1;
			server->ready = 0;
			res = false;
			if (!sbuf_pause(&client->sbuf))
				disconnect_client(client, true, "pause failed");
		} else
			res = true;
	} else {
		pause_client(client);
		res = false;
	}
	return res;
}
