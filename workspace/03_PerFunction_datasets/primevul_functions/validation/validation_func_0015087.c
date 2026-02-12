static int sctp_setsockopt_encap_port(struct sock *sk,
				      struct sctp_udpencaps *encap,
				      unsigned int optlen)
{
	struct sctp_association *asoc;
	struct sctp_transport *t;
	__be16 encap_port;

	if (optlen != sizeof(*encap))
		return -EINVAL;


	encap_port = (__force __be16)encap->sue_port;
	if (!sctp_is_any(sk, (union sctp_addr *)&encap->sue_address)) {
		t = sctp_addr_id2transport(sk, &encap->sue_address,
					   encap->sue_assoc_id);
		if (!t)
			return -EINVAL;

		t->encap_port = encap_port;
		return 0;
	}


	asoc = sctp_id2assoc(sk, encap->sue_assoc_id);
	if (!asoc && encap->sue_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		return -EINVAL;


	if (asoc) {
		list_for_each_entry(t, &asoc->peer.transport_addr_list,
				    transports)
			t->encap_port = encap_port;

		return 0;
	}

	sctp_sk(sk)->encap_port = encap_port;
	return 0;
}
