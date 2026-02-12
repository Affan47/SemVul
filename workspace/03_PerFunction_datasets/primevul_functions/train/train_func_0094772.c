static void received_response_to_ping(REQUEST *request)
{
	home_server *home;
	char buffer[128];

	rad_assert(request->home_server != NULL);

	home = request->home_server;
	home->num_received_pings++;

	radlog(L_PROXY, "Received response to status check %d (%d in current sequence)",
	       request->number, home->num_received_pings);


	fr_event_delete(el, &request->ev);
	remove_from_proxy_hash(request);
	rad_assert(request->in_request_hash == FALSE);


	if (home->state == HOME_STATE_ALIVE) return;


	if (home->num_received_pings < home->num_pings_to_alive) {
		return;
	}

	home->state = HOME_STATE_ALIVE;
	home->currently_outstanding = 0;
	home->revive_time = now;

	if (!fr_event_delete(el, &home->ev)) {
		RDEBUG2("Hmm... no event for home server.  Oh well.");
	}

	radlog(L_PROXY, "Marking home server %s port %d alive",
	       inet_ntop(request->proxy->dst_ipaddr.af,
			 &request->proxy->dst_ipaddr.ipaddr,
			 buffer, sizeof(buffer)),
	       request->proxy->dst_port);
}
