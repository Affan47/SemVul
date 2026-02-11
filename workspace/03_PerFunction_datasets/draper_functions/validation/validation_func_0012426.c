doshutdown(void) {
	isc_task_detach(&global_task);

	if (servers != NULL)
		isc_mem_put(mctx, servers, ns_total * sizeof(isc_sockaddr_t));

	if (localaddr != NULL)
		isc_mem_put(mctx, localaddr, sizeof(isc_sockaddr_t));

	if (tsigkey != NULL) {
		ddebug("Freeing TSIG key");
		dns_tsigkey_detach(&tsigkey);
	}

	if (sig0key != NULL) {
		ddebug("Freeing SIG(0) key");
		dst_key_free(&sig0key);
	}

	if (updatemsg != NULL)
		dns_message_destroy(&updatemsg);

	if (is_dst_up) {
		ddebug("Destroy DST lib");
		dst_lib_destroy();
		is_dst_up = ISC_FALSE;
	}

	cleanup_entropy(&entropy);

	lwres_conf_clear(lwctx);
	lwres_context_destroy(&lwctx);

	ddebug("Destroying request manager");
	dns_requestmgr_detach(&requestmgr);

	ddebug("Freeing the dispatchers");
	if (have_ipv4)
		dns_dispatch_detach(&dispatchv4);
	if (have_ipv6)
		dns_dispatch_detach(&dispatchv6);

	ddebug("Shutting down dispatch manager");
	dns_dispatchmgr_destroy(&dispatchmgr);

}
