ns_client_releasename(ns_client_t *client, dns_name_t **namep) {


	CTRACE("ns_client_releasename");
	client->query.attributes &= ~NS_QUERYATTR_NAMEBUFUSED;
	dns_message_puttempname(client->message, namep);
	CTRACE("ns_client_releasename: done");
}
