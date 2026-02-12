int sctp_auth_init_hmacs(struct sctp_endpoint *ep, gfp_t gfp)
{
	struct crypto_hash *tfm = NULL;
	__u16   id;


	if (!sctp_auth_enable) {
		ep->auth_hmacs = NULL;
		return 0;
	}

	if (ep->auth_hmacs)
		return 0;


	ep->auth_hmacs = kzalloc(
			    sizeof(struct crypto_hash *) * SCTP_AUTH_NUM_HMACS,
			    gfp);
	if (!ep->auth_hmacs)
		return -ENOMEM;

	for (id = 0; id < SCTP_AUTH_NUM_HMACS; id++) {


		if (!sctp_hmac_list[id].hmac_name)
			continue;


		if (ep->auth_hmacs[id])
			continue;


		tfm = crypto_alloc_hash(sctp_hmac_list[id].hmac_name, 0,
					CRYPTO_ALG_ASYNC);
		if (IS_ERR(tfm))
			goto out_err;

		ep->auth_hmacs[id] = tfm;
	}

	return 0;

out_err:

	sctp_auth_destroy_hmacs(ep->auth_hmacs);
	return -ENOMEM;
}
