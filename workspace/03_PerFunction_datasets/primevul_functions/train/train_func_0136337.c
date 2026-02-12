static void tag_pool_dirty(PgPool *pool)
{
	struct List *item, *tmp;
	struct PgSocket *server;


	if (pool->welcome_msg) {
		pktbuf_free(pool->welcome_msg);
		pool->welcome_msg = NULL;
	}
	pool->welcome_msg_ready = 0;


	for_each_server(pool, tag_dirty);


	statlist_for_each_safe(item, &pool->new_server_list, tmp) {
		server = container_of(item, PgSocket, head);
		disconnect_server(server, true, "connect string changed");
	}
}
