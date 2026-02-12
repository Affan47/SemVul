crypto_gq(
	struct exten *ep,
	struct peer *peer
	)
{
	RSA	*rsa;
	BN_CTX	*bctx;
	DSA_SIG	*sdsa;
	BIGNUM	*y, *v;
	const u_char *ptr;
	long	len;
	u_int	temp;


	if (peer->ident_pkey == NULL) {
		msyslog(LOG_NOTICE, "crypto_gq: scheme unavailable");
		return (XEVNT_ID);
	}
	if (ntohl(ep->fstamp) < peer->ident_pkey->fstamp) {
		msyslog(LOG_NOTICE, "crypto_gq: invalid filestamp %u",
		    ntohl(ep->fstamp));
		return (XEVNT_FSP);
	}
	if ((rsa = peer->ident_pkey->pkey->pkey.rsa) == NULL) {
		msyslog(LOG_NOTICE, "crypto_gq: defective key");
		return (XEVNT_PUB);
	}
	if (peer->iffval == NULL) {
		msyslog(LOG_NOTICE, "crypto_gq: missing challenge");
		return (XEVNT_ID);
	}


	bctx = BN_CTX_new(); y = BN_new(); v = BN_new();
	len = ntohl(ep->vallen);
	ptr = (u_char *)ep->pkt;
	if ((sdsa = d2i_DSA_SIG(NULL, &ptr, len)) == NULL) {
		BN_CTX_free(bctx); BN_free(y); BN_free(v);
		msyslog(LOG_ERR, "crypto_gq: %s",
		    ERR_error_string(ERR_get_error(), NULL));
		return (XEVNT_ERR);
	}


	if (peer->grpkey == NULL) {
		msyslog(LOG_NOTICE, "crypto_gq: missing group key");
		return (XEVNT_ID);
	}
	BN_mod_exp(v, peer->grpkey, peer->iffval, rsa->n, bctx);

	BN_mod_exp(y, sdsa->r, rsa->e, rsa->n, bctx);
	BN_mod_mul(y, v, y, rsa->n, bctx);


	bighash(y, y);
	temp = BN_cmp(y, sdsa->s);
	BN_CTX_free(bctx); BN_free(y); BN_free(v);
	BN_free(peer->iffval);
	peer->iffval = NULL;
	DSA_SIG_free(sdsa);
	if (temp == 0)
		return (XEVNT_OK);

	msyslog(LOG_NOTICE, "crypto_gq: identity not verified");
	return (XEVNT_ID);
}
