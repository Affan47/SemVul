struct sctp_chunk *sctp_process_asconf(struct sctp_association *asoc,
				       struct sctp_chunk *asconf)
{
	union sctp_addr_param *addr_param;
	struct sctp_addip_chunk *addip;
	struct sctp_chunk *asconf_ack;
	bool all_param_pass = true;
	struct sctp_addiphdr *hdr;
	int length = 0, chunk_len;
	union sctp_params param;
	__be16 err_code;
	__u32 serial;

	addip = (struct sctp_addip_chunk *)asconf->chunk_hdr;
	chunk_len = ntohs(asconf->chunk_hdr->length) -
		    sizeof(struct sctp_chunkhdr);
	hdr = (struct sctp_addiphdr *)asconf->skb->data;
	serial = ntohl(hdr->serial);


	length = sizeof(*hdr);
	addr_param = (union sctp_addr_param *)(asconf->skb->data + length);
	chunk_len -= length;


	length = ntohs(addr_param->p.length);
	chunk_len -= length;


	asconf_ack = sctp_make_asconf_ack(asoc, serial, chunk_len * 4);
	if (!asconf_ack)
		goto done;


	sctp_walk_params(param, addip, addip_hdr.params) {

		if (param.p->type == SCTP_PARAM_IPV4_ADDRESS ||
		    param.p->type == SCTP_PARAM_IPV6_ADDRESS)
			continue;

		err_code = sctp_process_asconf_param(asoc, asconf,
						     param.addip);


		if (err_code != SCTP_ERROR_NO_ERROR)
			all_param_pass = false;
		if (!all_param_pass)
			sctp_add_asconf_response(asconf_ack, param.addip->crr_id,
						 err_code, param.addip);


		if (err_code == SCTP_ERROR_RSRC_LOW)
			goto done;
	}
done:
	asoc->peer.addip_serial++;


	if (asconf_ack) {
		sctp_chunk_hold(asconf_ack);
		list_add_tail(&asconf_ack->transmitted_list,
			      &asoc->asconf_ack_list);
	}

	return asconf_ack;
}
