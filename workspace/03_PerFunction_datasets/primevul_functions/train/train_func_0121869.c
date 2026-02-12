dns_message_setsig0key(dns_message_t *msg, dst_key_t *key) {
	isc_region_t r;
	unsigned int x;
	isc_result_t result;


	REQUIRE(DNS_MESSAGE_VALID(msg));
	REQUIRE(msg->from_to_wire == DNS_MESSAGE_INTENTRENDER);
	REQUIRE(msg->state == DNS_SECTION_ANY);

	if (key != NULL) {
		REQUIRE(msg->sig0key == NULL && msg->tsigkey == NULL);
		dns_name_toregion(dst_key_name(key), &r);
		result = dst_key_sigsize(key, &x);
		if (result != ISC_R_SUCCESS) {
			msg->sig_reserved = 0;
			return (result);
		}
		msg->sig_reserved = 27 + r.length + x;
		result = dns_message_renderreserve(msg, msg->sig_reserved);
		if (result != ISC_R_SUCCESS) {
			msg->sig_reserved = 0;
			return (result);
		}
		msg->sig0key = key;
	}
	return (ISC_R_SUCCESS);
}
