crypto_bob(
	struct exten *ep,
	struct value *vp
	)
{
	DSA	*dsa;
	DSA_SIG	*sdsa;
	BN_CTX	*bctx;
	EVP_MD_CTX ctx;
	tstamp_t tstamp;
	BIGNUM	*bn, *bk, *r;
	u_char	*ptr;
	u_int	len;


	if (iffkey_info == NULL) {
		msyslog(LOG_NOTICE, "crypto_bob: scheme unavailable");
		return (XEVNT_ID);
	}
	dsa = iffkey_info->pkey->pkey.dsa;


	len = exten_payload_size(ep);
	if (len == 0 || len > MAX_VALLEN)
		return (XEVNT_LEN);
	if ((r = BN_bin2bn((u_char *)ep->pkt, len, NULL)) == NULL) {
		msyslog(LOG_ERR, "crypto_bob: %s",
		    ERR_error_string(ERR_get_error(), NULL));
		return (XEVNT_ERR);
	}


	bctx = BN_CTX_new(); bk = BN_new(); bn = BN_new();
	sdsa = DSA_SIG_new();
	BN_rand(bk, len * 8, -1, 1);
	BN_mod_mul(bn, dsa->priv_key, r, dsa->q, bctx);
	BN_add(bn, bn, bk);
	BN_mod(bn, bn, dsa->q, bctx);
	sdsa->r = BN_dup(bn);
	BN_mod_exp(bk, dsa->g, bk, dsa->p, bctx);
	bighash(bk, bk);
	sdsa->s = BN_dup(bk);
	BN_CTX_free(bctx);
	BN_free(r); BN_free(bn); BN_free(bk);
#ifdef DEBUG
	if (debug > 1)
		DSA_print_fp(stdout, dsa, 0);
#endif


	len = i2d_DSA_SIG(sdsa, NULL);
	if (len == 0) {
		msyslog(LOG_ERR, "crypto_bob: %s",
		    ERR_error_string(ERR_get_error(), NULL));
		DSA_SIG_free(sdsa);
		return (XEVNT_ERR);
	}
	if (len > MAX_VALLEN) {
		msyslog(LOG_ERR, "crypto_bob: signature is too big: %u",
		    len);
		DSA_SIG_free(sdsa);
		return (XEVNT_LEN);
	}
	memset(vp, 0, sizeof(struct value));
	tstamp = crypto_time();
	vp->tstamp = htonl(tstamp);
	vp->fstamp = htonl(iffkey_info->fstamp);
	vp->vallen = htonl(len);
	ptr = emalloc(len);
	vp->ptr = ptr;
	i2d_DSA_SIG(sdsa, &ptr);
	DSA_SIG_free(sdsa);
	if (tstamp == 0)
		return (XEVNT_OK);


	vp->sig = emalloc(sign_siglen);
	EVP_SignInit(&ctx, sign_digest);
	EVP_SignUpdate(&ctx, (u_char *)&vp->tstamp, 12);
	EVP_SignUpdate(&ctx, vp->ptr, len);
	if (EVP_SignFinal(&ctx, vp->sig, &len, sign_pkey)) {
		INSIST(len <= sign_siglen);
		vp->siglen = htonl(len);
	}
	return (XEVNT_OK);
}
