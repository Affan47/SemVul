void launch_new_connection(PgPool *pool)
{
	PgSocket *server;
	int total;


	if (!statlist_empty(&pool->new_server_list)) {
		log_debug("launch_new_connection: already progress");
		return;
	}


	if (pool->last_connect_failed) {
		usec_t now = get_cached_time();
		if (now - pool->last_connect_time < cf_server_login_retry) {
			log_debug("launch_new_connection: last failed, wait");
			return;
		}
	}


	total = pool_server_count(pool);
	if (total >= pool->db->pool_size && pool->welcome_msg_ready) {

		if (cf_res_pool_timeout && pool->db->res_pool_size) {
			usec_t now = get_cached_time();
			PgSocket *c = first_socket(&pool->waiting_client_list);
			if (c && (now - c->request_time) >= cf_res_pool_timeout) {
				if (total < pool->db->pool_size + pool->db->res_pool_size) {
					slog_warning(c, "Taking connection from reserve_pool");
					goto allow_new;
				}
			}
		}
		log_debug("launch_new_connection: pool full (%d >= %d)",
				total, pool->db->pool_size);
		return;
	}

allow_new:

	server = slab_alloc(server_cache);
	if (!server) {
		log_debug("launch_new_connection: no memory");
		return;
	}


	server->pool = pool;
	server->auth_user = server->pool->user;
	server->connect_time = get_cached_time();
	pool->last_connect_time = get_cached_time();
	change_server_state(server, SV_LOGIN);

	dns_connect(server);
}
