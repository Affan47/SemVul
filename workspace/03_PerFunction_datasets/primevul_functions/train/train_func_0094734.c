static void received_retransmit(REQUEST *request, const RADCLIENT *client)
{
#ifdef WITH_PROXY
	char buffer[128];
#endif

	RAD_STATS_TYPE_INC(request->listener, total_dup_requests);
	RAD_STATS_CLIENT_INC(request->listener, client, total_dup_requests);

	switch (request->child_state) {
	case REQUEST_QUEUED:
	case REQUEST_RUNNING:
#ifdef WITH_PROXY
	discard:
#endif
		radlog(L_ERR, "Discarding duplicate request from "
		       "client %s port %d - ID: %d due to unfinished request %u",
		       client->shortname,
		       request->packet->src_port,request->packet->id,
		       request->number);
		break;

#ifdef WITH_PROXY
	case REQUEST_PROXIED:


		if (request->packet->code != PW_AUTHENTICATION_REQUEST) {
			goto discard;
		}

		check_for_zombie_home_server(request);


		if ((request->packet->dst_port != 0) &&
		    (request->home_server->state == HOME_STATE_IS_DEAD)) {
			home_server *home;

			remove_from_proxy_hash(request);

			home = home_server_ldb(NULL, request->home_pool, request);
			if (!home) {
				RDEBUG2("Failed to find live home server for request %u", request->number);
			no_home_servers:


				post_proxy_fail_handler(request);
				return;
			}

			request->proxy->code = request->packet->code;


			free(request->proxy->data);
			request->proxy->data = NULL;
			request->proxy->data_len = 0;


			if (request->home_server->server) {
				proxy_fallback_handler(request);
				return;
			}


			if (!proxy_request(request)) {
				RDEBUG("ERROR: Failed to re-proxy request %u", request->number);
				goto no_home_servers;
			}


			rad_assert(request->next_callback != NULL);
			INSERT_EVENT(request->next_callback, request);
			request->next_callback = NULL;
			return;
		}

		RDEBUG2("Sending duplicate proxied request to home server %s port %d - ID: %d",
		       inet_ntop(request->proxy->dst_ipaddr.af,
				 &request->proxy->dst_ipaddr.ipaddr,
				 buffer, sizeof(buffer)),
		       request->proxy->dst_port,
		       request->proxy->id);
		request->num_proxied_requests++;

		DEBUG_PACKET(request, request->proxy, 1);
		request->proxy_listener->send(request->proxy_listener,
					      request);
		break;
#endif

	case REQUEST_REJECT_DELAY:
		RDEBUG2("Waiting to send Access-Reject "
		       "to client %s port %d - ID: %d",
		       client->shortname,
		       request->packet->src_port, request->packet->id);
		break;

	case REQUEST_CLEANUP_DELAY:
	case REQUEST_DONE:
		if (request->reply->code == 0) {
			RDEBUG2("Ignoring retransmit from client %s port %d "
				"- ID: %d, no reply was configured",
				client->shortname,
				request->packet->src_port, request->packet->id);
			return;
		}


		RDEBUG2("Sending duplicate reply "
		       "to client %s port %d - ID: %d",
		       client->shortname,
		       request->packet->src_port, request->packet->id);
		DEBUG_PACKET(request, request->reply, 1);
		request->listener->send(request->listener, request);
		break;
	}
}
