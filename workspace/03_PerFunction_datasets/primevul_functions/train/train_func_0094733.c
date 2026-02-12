REQUEST *received_proxy_response(RADIUS_PACKET *packet)
{
	char		buffer[128];
	REQUEST		*request;


	request = lookup_in_proxy_hash(packet);

	if (!request) {
		radlog(L_PROXY, "No outstanding request was found for reply from host %s port %d - ID %d",
		       inet_ntop(packet->src_ipaddr.af,
				 &packet->src_ipaddr.ipaddr,
				 buffer, sizeof(buffer)),
		       packet->src_port, packet->id);
		return NULL;
	}


	if (request->proxy_reply) {
		if (memcmp(request->proxy_reply->vector,
			   packet->vector,
			   sizeof(request->proxy_reply->vector)) == 0) {
			RDEBUG2("Discarding duplicate reply from host %s port %d  - ID: %d for request %u",
			       inet_ntop(packet->src_ipaddr.af,
					 &packet->src_ipaddr.ipaddr,
					 buffer, sizeof(buffer)),
			       packet->src_port, packet->id,
			       request->number);
		} else {


			RDEBUG2("Ignoring conflicting proxy reply");
		}


		return NULL;
	}


	if (rad_verify(packet, request->proxy,
		       request->home_server->secret) != 0) {
		DEBUG("Ignoring spoofed proxy reply.  Signature is invalid");
		return NULL;
	}

	gettimeofday(&now, NULL);


	if (!request->packet) {
		request->proxy_reply = packet;
		received_response_to_ping(request);
		request->proxy_reply = NULL;
		ev_request_free(&request);
		return NULL;
	}


	request->home_server->state = HOME_STATE_ALIVE;

#ifdef WITH_COA


	if (request->parent && (request->parent->coa == request)) {
		request->parent->coa = NULL;
		request->parent = NULL;


	} else if ((request->packet->code != request->proxy->code) &&
		   ((request->proxy->code == PW_COA_REQUEST) ||
		    (request->proxy->code == PW_DISCONNECT_REQUEST))) {


	} else


#endif


	if (request->reply && request->reply->code != 0) {
		RDEBUG2("Ignoring proxy reply that arrived after we sent a reply to the NAS");
		return NULL;
	}

#ifdef WITH_STATS


	if (request->home_server->ema.window > 0) {
		radius_stats_ema(&request->home_server->ema,
				 &now, &request->proxy_when);
	}
#endif

	switch (request->child_state) {
	case REQUEST_QUEUED:
	case REQUEST_RUNNING:
		radlog(L_ERR, "Internal sanity check failed for child state");


	case REQUEST_REJECT_DELAY:
	case REQUEST_CLEANUP_DELAY:
	case REQUEST_DONE:
		radlog(L_ERR, "Reply from home server %s port %d  - ID: %d arrived too late for request %u. Try increasing 'retry_delay' or 'max_request_time'",
		       inet_ntop(packet->src_ipaddr.af,
				 &packet->src_ipaddr.ipaddr,
				 buffer, sizeof(buffer)),
		       packet->src_port, packet->id,
		       request->number);

		return NULL;

	case REQUEST_PROXIED:
		break;
	}

	request->proxy_reply = packet;

#if 0


	if ((request->num_proxied_responses == 1)
		int rtt;
		home_server *home = request->home_server;

		rtt = now.tv_sec - request->proxy_when.tv_sec;
		rtt *= USEC;
		rtt += now.tv_usec;
		rtt -= request->proxy_when.tv_usec;

		if (!home->has_rtt) {
			home->has_rtt = TRUE;

			home->srtt = rtt;
			home->rttvar = rtt / 2;

		} else {
			home->rttvar -= home->rttvar >> 2;
			home->rttvar += (home->srtt - rtt);
			home->srtt -= home->srtt >> 3;
			home->srtt += rtt >> 3;
		}

		home->rto = home->srtt;
		if (home->rttvar > (USEC / 4)) {
			home->rto += home->rttvar * 4;
		} else {
			home->rto += USEC;
		}
	}
