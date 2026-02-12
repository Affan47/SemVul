dns_message_renderchangebuffer(dns_message_t *msg, isc_buffer_t *buffer) {
	isc_region_t r, rn;

	REQUIRE(DNS_MESSAGE_VALID(msg));
	REQUIRE(buffer != NULL);
	REQUIRE(msg->buffer != NULL);


	isc_buffer_clear(buffer);

	isc_buffer_availableregion(buffer, &rn);
	isc_buffer_usedregion(msg->buffer, &r);
	REQUIRE(rn.length > r.length);


	isc_buffer_add(buffer, r.length);
	memmove(rn.base, r.base, r.length);

	msg->buffer = buffer;

	return (ISC_R_SUCCESS);
}
