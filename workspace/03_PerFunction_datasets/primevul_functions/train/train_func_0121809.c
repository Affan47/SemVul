dns_message_getsig0(dns_message_t *msg, dns_name_t **owner) {


	REQUIRE(DNS_MESSAGE_VALID(msg));
	REQUIRE(owner == NULL || *owner == NULL);

	if (msg->sig0 != NULL && owner != NULL) {


		if (msg->sig0name == NULL)
			*owner = dns_rootname;
		else
			*owner = msg->sig0name;
	}
	return (msg->sig0);
}
