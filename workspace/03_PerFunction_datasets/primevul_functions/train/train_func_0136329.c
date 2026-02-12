static bool reuse_on_release(PgSocket *server)
{
	bool res = true;
	PgPool *pool = server->pool;
	PgSocket *client = first_socket(&pool->waiting_client_list);
	if (client) {
		activate_client(client);


		if (server->state == SV_FREE || server->state == SV_JUSTFREE)
			res = false;
	}
	return res;
}
