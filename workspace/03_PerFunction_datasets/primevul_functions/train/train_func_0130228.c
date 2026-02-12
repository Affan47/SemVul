innodb_conn_clean(

	innodb_engine_t*	engine,

	bool			clear_all,
	bool			has_lock)
{
	innodb_conn_data_t*	conn_data;
	innodb_conn_data_t*	next_conn_data;
	int			num_freed = 0;
	void*			thd = NULL;

	if (engine->enable_binlog && clear_all) {
		thd = handler_create_thd(true);
	}

	LOCK_CONN_IF_NOT_LOCKED(has_lock, engine);

	conn_data = UT_LIST_GET_FIRST(engine->conn_data);

	while (conn_data) {
		void*	cookie = conn_data->conn_cookie;

		next_conn_data = UT_LIST_GET_NEXT(conn_list, conn_data);

		if (!clear_all && !conn_data->in_use) {
			innodb_conn_data_t*	check_data;
			check_data = engine->server.cookie->get_engine_specific(
				cookie);


			if (!check_data || check_data != conn_data) {
				assert(conn_data->is_stale);
			}
		}


		if (conn_data->is_stale) {


			if (engine->clean_stale_conn)
				break;

			UT_LIST_REMOVE(conn_list, engine->conn_data,
				       conn_data);
			innodb_conn_clean_data(conn_data, false, true);
			num_freed++;
		} else {
			if (clear_all) {
				UT_LIST_REMOVE(conn_list, engine->conn_data,
					       conn_data);

				if (thd) {
					handler_thd_attach(conn_data->thd,
							   NULL);
				}

				innodb_reset_conn(conn_data, false, true,
						  engine->enable_binlog);
				if (conn_data->thd) {
					handler_thd_attach(
						conn_data->thd, NULL);
				}
				innodb_conn_clean_data(conn_data, false, true);

				engine->server.cookie->store_engine_specific(
					cookie, NULL);
				num_freed++;
			}
		}

		conn_data = next_conn_data;
	}

	assert(!clear_all || engine->conn_data.count == 0);

	UNLOCK_CONN_IF_NOT_LOCKED(has_lock, engine);

	if (thd) {
		handler_thd_attach(thd, NULL);
		handler_close_thd(thd);
	}

	return(num_freed);
}
