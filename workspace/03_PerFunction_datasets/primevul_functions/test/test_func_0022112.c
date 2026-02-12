int sctp_verify_init(const struct sctp_association *asoc,
		     sctp_cid_t cid,
		     sctp_init_chunk_t *peer_init,
		     struct sctp_chunk *chunk,
		     struct sctp_chunk **errp)
{
	union sctp_params param;
	int has_cookie = 0;
	int result;


	if ((0 == peer_init->init_hdr.num_outbound_streams) ||
	    (0 == peer_init->init_hdr.num_inbound_streams) ||
	    (0 == peer_init->init_hdr.init_tag) ||
	    (SCTP_DEFAULT_MINWINDOW > ntohl(peer_init->init_hdr.a_rwnd))) {

		return sctp_process_inv_mandatory(asoc, chunk, errp);
	}


	sctp_walk_params(param, peer_init, init_hdr.params) {

		if (SCTP_PARAM_STATE_COOKIE == param.p->type)
			has_cookie = 1;

	}


	if (param.v != (void*)chunk->chunk_end)
		return sctp_process_inv_paramlength(asoc, param.p, chunk, errp);


	if ((SCTP_CID_INIT_ACK == cid) && !has_cookie)
		return sctp_process_missing_param(asoc, SCTP_PARAM_STATE_COOKIE,
						  chunk, errp);


	sctp_walk_params(param, peer_init, init_hdr.params) {

		result = sctp_verify_param(asoc, param, cid, chunk, errp);
		switch (result) {
		    case SCTP_IERROR_ABORT:
		    case SCTP_IERROR_NOMEM:
				return 0;
		    case SCTP_IERROR_ERROR:
				return 1;
		    case SCTP_IERROR_NO_ERROR:
		    default:
				break;
		}

	}

	return 1;
}
