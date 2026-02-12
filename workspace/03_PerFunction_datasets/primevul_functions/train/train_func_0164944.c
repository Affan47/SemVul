void sctp_auth_asoc_set_default_hmac(struct sctp_association *asoc,
				     struct sctp_hmac_algo_param *hmacs)
{
	struct sctp_endpoint *ep;
	__u16   id;
	int	i;
	int	n_params;


	if (asoc->default_hmac_id)
		return;

	n_params = (ntohs(hmacs->param_hdr.length)
				- sizeof(sctp_paramhdr_t)) >> 1;
	ep = asoc->ep;
	for (i = 0; i < n_params; i++) {
		id = ntohs(hmacs->hmac_ids[i]);


		if (id > SCTP_AUTH_HMAC_ID_MAX)
			continue;


		if (ep->auth_hmacs[id]) {
			asoc->default_hmac_id = id;
			break;
		}
	}
}
