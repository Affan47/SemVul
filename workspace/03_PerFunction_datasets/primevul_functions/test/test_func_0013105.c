struct sctp_chunk *sctp_make_cookie_ack(const struct sctp_association *asoc,
					const struct sctp_chunk *chunk)
{
	struct sctp_chunk *retval;

	retval = sctp_make_control(asoc, SCTP_CID_COOKIE_ACK, 0, 0, GFP_ATOMIC);


	if (retval && chunk && chunk->transport)
		retval->transport =
			sctp_assoc_lookup_paddr(asoc,
						&chunk->transport->ipaddr);

	return retval;
}
