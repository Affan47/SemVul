dns_message_getopt(dns_message_t *msg) {


	REQUIRE(DNS_MESSAGE_VALID(msg));

	return (msg->opt);
}
