client_senddone(isc_nmhandle_t *handle, isc_result_t result, void *cbarg) {
	ns_client_t *client = cbarg;

	REQUIRE(client->sendhandle == handle);

	CTRACE("senddone");


	client->sendhandle = NULL;

	if (result != ISC_R_SUCCESS) {
		if (!TCP_CLIENT(client) && result == ISC_R_MAXSIZE) {
			ns_client_log(client, DNS_LOGCATEGORY_SECURITY,
				      NS_LOGMODULE_CLIENT, ISC_LOG_DEBUG(3),
				      "send exceeded maximum size: truncating");
			client->query.attributes &= ~NS_QUERYATTR_ANSWERED;
			client->rcode_override = dns_rcode_noerror;
			ns_client_error(client, ISC_R_MAXSIZE);
		} else {
			ns_client_log(client, DNS_LOGCATEGORY_SECURITY,
				      NS_LOGMODULE_CLIENT, ISC_LOG_DEBUG(3),
				      "send failed: %s",
				      isc_result_totext(result));
		}
	}

	isc_nmhandle_detach(&handle);
}
