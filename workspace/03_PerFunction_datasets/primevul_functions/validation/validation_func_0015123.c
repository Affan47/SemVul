static int sctp_setsockopt_peer_addr_params(struct sock *sk,
					    struct sctp_paddrparams *params,
					    unsigned int optlen)
{
	struct sctp_transport   *trans = NULL;
	struct sctp_association *asoc = NULL;
	struct sctp_sock        *sp = sctp_sk(sk);
	int error;
	int hb_change, pmtud_change, sackdelay_change;

	if (optlen == ALIGN(offsetof(struct sctp_paddrparams,
					    spp_ipv6_flowlabel), 4)) {
		if (params->spp_flags & (SPP_DSCP | SPP_IPV6_FLOWLABEL))
			return -EINVAL;
	} else if (optlen != sizeof(*params)) {
		return -EINVAL;
	}


	hb_change        = params->spp_flags & SPP_HB;
	pmtud_change     = params->spp_flags & SPP_PMTUD;
	sackdelay_change = params->spp_flags & SPP_SACKDELAY;

	if (hb_change        == SPP_HB ||
	    pmtud_change     == SPP_PMTUD ||
	    sackdelay_change == SPP_SACKDELAY ||
	    params->spp_sackdelay > 500 ||
	    (params->spp_pathmtu &&
	     params->spp_pathmtu < SCTP_DEFAULT_MINSEGMENT))
		return -EINVAL;


	if (!sctp_is_any(sk, (union sctp_addr *)&params->spp_address)) {
		trans = sctp_addr_id2transport(sk, &params->spp_address,
					       params->spp_assoc_id);
		if (!trans)
			return -EINVAL;
	}


	asoc = sctp_id2assoc(sk, params->spp_assoc_id);
	if (!asoc && params->spp_assoc_id != SCTP_FUTURE_ASSOC &&
	    sctp_style(sk, UDP))
		return -EINVAL;


	if (params->spp_flags & SPP_HB_DEMAND && !trans && !asoc)
		return -EINVAL;


	error = sctp_apply_peer_addr_params(params, trans, asoc, sp,
					    hb_change, pmtud_change,
					    sackdelay_change);

	if (error)
		return error;


	if (!trans && asoc) {
		list_for_each_entry(trans, &asoc->peer.transport_addr_list,
				transports) {
			sctp_apply_peer_addr_params(params, trans, asoc, sp,
						    hb_change, pmtud_change,
						    sackdelay_change);
		}
	}

	return 0;
}
