static int originated_coa_request(REQUEST *request)
{
	int delay, rcode, pre_proxy_type = 0;
	VALUE_PAIR *vp;
	REQUEST *coa;
	fr_ipaddr_t ipaddr;
	char buffer[256];

	rad_assert(request->proxy == NULL);
	rad_assert(!request->in_proxy_hash);
	rad_assert(request->proxy_reply == NULL);


	vp = pairfind(request->config_items, PW_SEND_COA_REQUEST);
	if (!vp && request->coa) {
		vp = pairfind(request->coa->proxy->vps, PW_SEND_COA_REQUEST);
	}

	if (vp) {
		if (vp->vp_integer == 0) {
			ev_request_free(&request->coa);
			return 1;
		}
	}

	if (!request->coa) request_alloc_coa(request);
	if (!request->coa) return 0;

	coa = request->coa;


	memset(&ipaddr, 0, sizeof(ipaddr));
	vp = pairfind(coa->proxy->vps, PW_PACKET_DST_IP_ADDRESS);
	if (vp) {
		ipaddr.af = AF_INET;
		ipaddr.ipaddr.ip4addr.s_addr = vp->vp_ipaddr;

	} else if ((vp = pairfind(coa->proxy->vps,
				  PW_PACKET_DST_IPV6_ADDRESS)) != NULL) {
		ipaddr.af = AF_INET6;
		ipaddr.ipaddr.ip6addr = vp->vp_ipv6addr;

	} else if ((vp = pairfind(coa->proxy->vps,
				  PW_HOME_SERVER_POOL)) != NULL) {
		coa->home_pool = home_pool_byname(vp->vp_strvalue,
						  HOME_TYPE_COA);
		if (!coa->home_pool) {
			RDEBUG2("WARNING: No such home_server_pool %s",
			       vp->vp_strvalue);
	fail:
			ev_request_free(&request->coa);
			return 0;
		}


	} else if (request->client->coa_pool) {
		coa->home_pool = request->client->coa_pool;

	} else if (request->client->coa_server) {
		coa->home_server = request->client->coa_server;

	} else {


		memcpy(&ipaddr, &request->packet->src_ipaddr, sizeof(ipaddr));
	}


	if (coa->home_pool) {
		coa->home_server = home_server_ldb(NULL, coa->home_pool, coa);
		if (!coa->home_server) {
			RDEBUG("WARNING: No live home server for home_server_pool %s", vp->vp_strvalue);
			goto fail;
		}

	} else if (!coa->home_server) {
		int port = PW_COA_UDP_PORT;

		vp = pairfind(coa->proxy->vps, PW_PACKET_DST_PORT);
		if (vp) port = vp->vp_integer;

		coa->home_server = home_server_find(&ipaddr, port);
		if (!coa->home_server) {
			RDEBUG2("WARNING: Unknown destination %s:%d for CoA request.",
			       inet_ntop(ipaddr.af, &ipaddr.ipaddr,
					 buffer, sizeof(buffer)), port);
			goto fail;
		}
	}

	vp = pairfind(coa->proxy->vps, PW_PACKET_TYPE);
	if (vp) {
		switch (vp->vp_integer) {
		case PW_COA_REQUEST:
		case PW_DISCONNECT_REQUEST:
			coa->proxy->code = vp->vp_integer;
			break;

		default:
			DEBUG("Cannot set CoA Packet-Type to code %d",
			      vp->vp_integer);
			goto fail;
		}
	}

	if (!coa->proxy->code) coa->proxy->code = PW_COA_REQUEST;


	rad_assert(coa->packet != NULL);
	rad_assert(coa->packet->vps == NULL);
	memcpy(coa->packet, request->packet, sizeof(*request->packet));
	coa->packet->vps = paircopy(request->packet->vps);
	coa->packet->data = NULL;
	rad_assert(coa->reply != NULL);
	rad_assert(coa->reply->vps == NULL);
	memcpy(coa->reply, request->reply, sizeof(*request->reply));
	coa->reply->vps = paircopy(request->reply->vps);
	coa->reply->data = NULL;
	coa->config_items = paircopy(request->config_items);


	vp = pairfind(request->config_items, PW_PRE_PROXY_TYPE);
	if (vp) {
		RDEBUG2("  Found Pre-Proxy-Type %s", vp->vp_strvalue);
		pre_proxy_type = vp->vp_integer;
	}

	if (coa->home_pool && coa->home_pool->virtual_server) {
		const char *old_server = coa->server;

		coa->server = coa->home_pool->virtual_server;
		RDEBUG2(" server %s {", coa->server);
		rcode = module_pre_proxy(pre_proxy_type, coa);
		RDEBUG2(" }");
		coa->server = old_server;
	} else {
		rcode = module_pre_proxy(pre_proxy_type, coa);
	}
	switch (rcode) {
	default:
		goto fail;


	case RLM_MODULE_NOOP:
	case RLM_MODULE_OK:
	case RLM_MODULE_UPDATED:
		break;
	}


	coa->proxy->dst_ipaddr = coa->home_server->ipaddr;
	coa->proxy->dst_port = coa->home_server->port;

	if (!insert_into_proxy_hash(coa, FALSE)) {
		DEBUG("ERROR: Failed inserting CoA request into proxy hash.");
		goto fail;
	}


	request = coa;

	gettimeofday(&request->proxy_when, NULL);
	request->received = request->next_when = request->proxy_when;
	rad_assert(request->proxy_reply == NULL);


	delay = (fr_rand() & ((1 << 22) - 1)) / 10;
	request->delay = delay * request->home_server->coa_irt;
	delay = request->home_server->coa_irt * USEC;
	delay -= delay / 10;
	delay += request->delay;

	request->delay = delay;
	tv_add(&request->next_when, delay);
	request->next_callback = retransmit_coa_request;


	request->num_proxied_requests = 1;
	request->num_proxied_responses = 0;
#ifdef HAVE_PTHREAD_H
	request->child_pid = NO_SUCH_CHILD_PID;
#endif

	update_event_timestamp(request->proxy, request->proxy_when.tv_sec);

	request->child_state = REQUEST_PROXIED;

	DEBUG_PACKET(request, request->proxy, 1);

	request->proxy_listener->send(request->proxy_listener,
				      request);
	return 1;
}
