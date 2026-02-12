void accept_cancel_request(PgSocket *req)
{
	struct List *pitem, *citem;
	PgPool *pool = NULL;
	PgSocket *server = NULL, *client, *main_client = NULL;

	Assert(req->state == CL_LOGIN);


	statlist_for_each(pitem, &pool_list) {
		pool = container_of(pitem, PgPool, head);
		statlist_for_each(citem, &pool->active_client_list) {
			client = container_of(citem, PgSocket, head);
			if (memcmp(client->cancel_key, req->cancel_key, 8) == 0) {
				main_client = client;
				goto found;
			}
		}
	}
found:


	if (!main_client) {
		disconnect_client(req, false, "failed cancel request");
		return;
	}


	if (!main_client->link) {
		bool res;


		if (main_client->pool->db->admin) {
			disconnect_client(req, false, "cancel request for console client");
			admin_handle_cancel(main_client);
			return;
		}

		disconnect_client(req, false, "cancel request for idle client");


		SEND_ReadyForQuery(res, main_client);
		if (!res)
			disconnect_client(main_client, true, "ReadyForQuery for main_client failed");
		return;
	}


	if (!sbuf_close(&req->sbuf))
		log_noise("sbuf_close failed, retry later");


	server = main_client->link;
	memcpy(req->cancel_key, server->cancel_key, 8);


	req->pool = pool;
	change_client_state(req, CL_CANCEL);


	launch_new_connection(pool);
}
