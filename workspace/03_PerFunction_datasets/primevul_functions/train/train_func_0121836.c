dns_message_renderend(dns_message_t *msg) {
	isc_buffer_t tmpbuf;
	isc_region_t r;
	int result;
	unsigned int count;

	REQUIRE(DNS_MESSAGE_VALID(msg));
	REQUIRE(msg->buffer != NULL);

	if ((msg->rcode & ~DNS_MESSAGE_RCODE_MASK) != 0 && msg->opt == NULL) {


		return (DNS_R_FORMERR);
	}


	if ((msg->tsigkey != NULL || msg->sig0key != NULL || msg->opt) &&
	    (msg->flags & DNS_MESSAGEFLAG_TC) != 0)
	{
		isc_buffer_t *buf;

		msgresetnames(msg, DNS_SECTION_ANSWER);
		buf = msg->buffer;
		dns_message_renderreset(msg);
		msg->buffer = buf;
		isc_buffer_clear(msg->buffer);
		isc_buffer_add(msg->buffer, DNS_MESSAGE_HEADERLEN);
		dns_compress_rollback(msg->cctx, 0);
		result = dns_message_rendersection(msg, DNS_SECTION_QUESTION,
						   0);
		if (result != ISC_R_SUCCESS && result != ISC_R_NOSPACE)
			return (result);
	}


	if (msg->opt != NULL) {
		dns_message_renderrelease(msg, msg->opt_reserved);
		msg->opt_reserved = 0;


		msg->opt->ttl &= ~DNS_MESSAGE_EDNSRCODE_MASK;
		msg->opt->ttl |= ((msg->rcode << 20) &
				  DNS_MESSAGE_EDNSRCODE_MASK);


		count = 0;
		result = renderset(msg->opt, dns_rootname, msg->cctx,
				   msg->buffer, msg->reserved, 0, &count);
		msg->counts[DNS_SECTION_ADDITIONAL] += count;
		if (result != ISC_R_SUCCESS)
			return (result);
	}


	if (msg->tsigkey != NULL) {
		dns_message_renderrelease(msg, msg->sig_reserved);
		msg->sig_reserved = 0;
		result = dns_tsig_sign(msg);
		if (result != ISC_R_SUCCESS)
			return (result);
		count = 0;
		result = renderset(msg->tsig, msg->tsigname, msg->cctx,
				   msg->buffer, msg->reserved, 0, &count);
		msg->counts[DNS_SECTION_ADDITIONAL] += count;
		if (result != ISC_R_SUCCESS)
			return (result);
	}


	if (msg->sig0key != NULL) {
		dns_message_renderrelease(msg, msg->sig_reserved);
		msg->sig_reserved = 0;
		result = dns_dnssec_signmessage(msg, msg->sig0key);
		if (result != ISC_R_SUCCESS)
			return (result);
		count = 0;


		result = renderset(msg->sig0, dns_rootname, msg->cctx,
				   msg->buffer, msg->reserved, 0, &count);
		msg->counts[DNS_SECTION_ADDITIONAL] += count;
		if (result != ISC_R_SUCCESS)
			return (result);
	}

	isc_buffer_usedregion(msg->buffer, &r);
	isc_buffer_init(&tmpbuf, r.base, r.length);

	dns_message_renderheader(msg, &tmpbuf);

	msg->buffer = NULL;

	return (ISC_R_SUCCESS);
}
