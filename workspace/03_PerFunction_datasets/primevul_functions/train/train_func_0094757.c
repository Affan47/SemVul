static int process_proxy_reply(REQUEST *request)
{
	int rcode;
	int post_proxy_type = 0;
	VALUE_PAIR *vp;


	pairfree(&request->reply->vps);


	vp = pairfind(request->config_items, PW_POST_PROXY_TYPE);
	if (vp) {
		RDEBUG2("  Found Post-Proxy-Type %s", vp->vp_strvalue);
		post_proxy_type = vp->vp_integer;
	}

	if (request->home_pool && request->home_pool->virtual_server) {
		const char *old_server = request->server;

		request->server = request->home_pool->virtual_server;
		RDEBUG2(" server %s {", request->server);
		rcode = module_post_proxy(post_proxy_type, request);
		RDEBUG2(" }");
		request->server = old_server;
	} else {
		rcode = module_post_proxy(post_proxy_type, request);
	}

#ifdef WITH_COA
	if (request->packet->code == request->proxy->code)


#endif


	if (request->proxy_reply) {


		pairdelete(&request->proxy_reply->vps, PW_PROXY_STATE);


		pairadd(&request->reply->vps, request->proxy_reply->vps);
		request->proxy_reply->vps = NULL;


		pairfree(&request->proxy->vps);
	}

	switch (rcode) {
	default:
		break;
	case RLM_MODULE_FAIL:

		request->child_state = REQUEST_DONE;
		return 0;

	case RLM_MODULE_HANDLED:

		request->child_state = REQUEST_DONE;
		return 0;
	}

	return 1;
}
