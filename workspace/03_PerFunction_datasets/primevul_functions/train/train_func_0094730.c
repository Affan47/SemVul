static void request_post_handler(REQUEST *request)
{
	int child_state = -1;
	struct timeval when;
	VALUE_PAIR *vp;

	if ((request->master_state == REQUEST_STOP_PROCESSING) ||
	    (request->parent &&
	     (request->parent->master_state == REQUEST_STOP_PROCESSING))) {
		RDEBUG2("request %u was cancelled.", request->number);
#ifdef HAVE_PTHREAD_H
		request->child_pid = NO_SUCH_CHILD_PID;
#endif
		child_state = REQUEST_DONE;
		goto cleanup;
	}

	if (request->child_state != REQUEST_RUNNING) {
		rad_panic("Internal sanity check failed");
	}

#ifdef WITH_COA


	if (!request->in_request_hash &&
	    request->proxy &&
	    ((request->proxy->code == PW_COA_REQUEST) ||
	     (request->proxy->code == PW_DISCONNECT_REQUEST))) {
		request->next_callback = NULL;
		child_state = REQUEST_DONE;
		goto cleanup;
	}
#endif


	if ((request->packet->code == PW_AUTHENTICATION_REQUEST) &&
	    (request->reply->code == 0) &&
	    ((vp = pairfind(request->config_items, PW_AUTH_TYPE)) != NULL) &&
	    (vp->vp_integer == PW_AUTHTYPE_REJECT)) {
		request->reply->code = PW_AUTHENTICATION_REJECT;
	}

#ifdef WITH_PROXY
	if (request->root->proxy_requests &&
	    !request->in_proxy_hash &&
	    (request->reply->code == 0) &&
	    (request->packet->dst_port != 0) &&
	    (request->packet->code != PW_STATUS_SERVER)) {
		int rcode = successfully_proxied_request(request);

		if (rcode == 1) return;


		if ((rcode < 0) && setup_post_proxy_fail(request)) {
			request_pre_handler(request);
		}


	}

#ifdef WITH_COA
	else if (request->proxy && request->coa) {
		RDEBUG("WARNING: Cannot proxy and originate CoA packets at the same time.  Cancelling CoA request");
		ev_request_free(&request->coa);
	}
#endif
#endif


	if (request->packet->dst_port == 0) {

#ifdef HAVE_PTHREAD_H
		request->child_pid = NO_SUCH_CHILD_PID;
#endif
		request->child_state = REQUEST_DONE;
		return;
	}

#ifdef WITH_PROXY


	vp = paircopy2(request->packet->vps, PW_PROXY_STATE);
	if (vp) pairadd(&request->reply->vps, vp);
#endif


	switch (request->packet->code) {
	case PW_AUTHENTICATION_REQUEST:
		gettimeofday(&request->next_when, NULL);

		if (request->reply->code == 0) {


			vp = pairfind(request->config_items,
				      PW_RESPONSE_PACKET_TYPE);
			if (!vp) {
				RDEBUG2("There was no response configured: rejecting request %u",
				       request->number);
				request->reply->code = PW_AUTHENTICATION_REJECT;

			} else if (vp->vp_integer == 256) {
				RDEBUG2("Not responding to request %u",
				       request->number);


				request->next_when.tv_sec += request->root->max_request_time;
				request->next_callback = cleanup_delay;
				child_state = REQUEST_CLEANUP_DELAY;
				break;
			} else {
				request->reply->code = vp->vp_integer;

			}
		}


		if (request->reply->code == PW_AUTHENTICATION_REJECT) {
			pairdelete(&request->config_items, PW_POST_AUTH_TYPE);
			vp = radius_pairmake(request, &request->config_items,
					     "Post-Auth-Type", "Reject",
					     T_OP_SET);
			if (vp) rad_postauth(request);


			when = request->received;
			when.tv_sec += request->root->reject_delay;

			if (timercmp(&when, &request->next_when, >)) {
				RDEBUG2("Delaying reject of request %u for %d seconds",
				       request->number,
				       request->root->reject_delay);
				request->next_when = when;
				request->next_callback = reject_delay;
#ifdef HAVE_PTHREAD_H
				request->child_pid = NO_SUCH_CHILD_PID;
#endif
				request->child_state = REQUEST_REJECT_DELAY;
				return;
			}
		}

#ifdef WITH_COA
	case PW_COA_REQUEST:
	case PW_DISCONNECT_REQUEST:
#endif
		request->next_when.tv_sec += request->root->cleanup_delay;
		request->next_callback = cleanup_delay;
		child_state = REQUEST_CLEANUP_DELAY;
		break;

	case PW_ACCOUNTING_REQUEST:
		request->next_callback = NULL;
		child_state = REQUEST_DONE;
		break;


	case PW_STATUS_SERVER:
		request->next_callback = NULL;
		child_state = REQUEST_DONE;
		break;

	default:


		request->next_callback = NULL;
		child_state = REQUEST_DONE;
		break;
	}


	if ((request->reply->code != 0) ||
	    (request->listener->type == RAD_LISTEN_DETAIL)) {
		DEBUG_PACKET(request, request->reply, 1);
		request->listener->send(request->listener, request);
	}

#ifdef WITH_COA


	if (!request->proxy &&
	    (request->coa ||
	     (pairfind(request->config_items, PW_SEND_COA_REQUEST) != NULL))) {
		if (!originated_coa_request(request)) {
			RDEBUG2("Do CoA Fail handler here");
		}

	}
#endif

 cleanup:


	pairfree(&request->config_items);

	pairfree(&request->packet->vps);
	request->username = NULL;
	request->password = NULL;

	pairfree(&request->reply->vps);

#ifdef WITH_PROXY
	if (request->proxy) {
		pairfree(&request->proxy->vps);

		if (request->proxy_reply) {
			pairfree(&request->proxy_reply->vps);
		}

#if 0


		if (!request->in_proxy_hash) {
			rad_free(&request->proxy);
			rad_free(&request->proxy_reply);
			request->home_server = NULL;
		}
#endif
	}
#endif

	RDEBUG2("Finished request %u.", request->number);
	rad_assert(child_state >= 0);
	request->child_state = child_state;


	if (!have_children) wait_a_bit(request);
}
