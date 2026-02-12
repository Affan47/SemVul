static __be16 sctp_process_asconf_param(struct sctp_association *asoc,
				       struct sctp_chunk *asconf,
				       sctp_addip_param_t *asconf_param)
{
	struct sctp_transport *peer;
	struct sctp_af *af;
	union sctp_addr	addr;
	union sctp_addr_param *addr_param;

	addr_param = (union sctp_addr_param *)
			((void *)asconf_param + sizeof(sctp_addip_param_t));

	switch (addr_param->v4.param_hdr.type) {
	case SCTP_PARAM_IPV6_ADDRESS:
		if (!asoc->peer.ipv6_address)
			return SCTP_ERROR_INV_PARAM;
		break;
	case SCTP_PARAM_IPV4_ADDRESS:
		if (!asoc->peer.ipv4_address)
			return SCTP_ERROR_INV_PARAM;
		break;
	default:
		return SCTP_ERROR_INV_PARAM;
	}

	af = sctp_get_af_specific(param_type2af(addr_param->v4.param_hdr.type));
	if (unlikely(!af))
		return SCTP_ERROR_INV_PARAM;

	af->from_addr_param(&addr, addr_param, htons(asoc->peer.port), 0);


	if (!af->is_any(&addr) && !af->addr_valid(&addr, NULL, asconf->skb))
		return SCTP_ERROR_INV_PARAM;

	switch (asconf_param->param_hdr.type) {
	case SCTP_PARAM_ADD_IP:


		if (af->is_any(&addr))
			memcpy(&addr, &asconf->source, sizeof(addr));


		peer = sctp_assoc_add_peer(asoc, &addr, GFP_ATOMIC, SCTP_UNCONFIRMED);
		if (!peer)
			return SCTP_ERROR_RSRC_LOW;


		if (!mod_timer(&peer->hb_timer, sctp_transport_timeout(peer)))
			sctp_transport_hold(peer);
		break;
	case SCTP_PARAM_DEL_IP:


		if (asoc->peer.transport_count == 1)
			return SCTP_ERROR_DEL_LAST_IP;


		if (sctp_cmp_addr_exact(sctp_source(asconf), &addr))
			return SCTP_ERROR_DEL_SRC_IP;


		if (af->is_any(&addr)) {
			sctp_assoc_set_primary(asoc, asconf->transport);
			sctp_assoc_del_nonprimary_peers(asoc,
							asconf->transport);
		} else
			sctp_assoc_del_peer(asoc, &addr);
		break;
	case SCTP_PARAM_SET_PRIMARY:


		if (af->is_any(&addr))
			memcpy(&addr.v4, sctp_source(asconf), sizeof(addr));

		peer = sctp_assoc_lookup_paddr(asoc, &addr);
		if (!peer)
			return SCTP_ERROR_INV_PARAM;

		sctp_assoc_set_primary(asoc, peer);
		break;
	default:
		return SCTP_ERROR_INV_PARAM;
		break;
	}

	return SCTP_ERROR_NO_ERROR;
}
