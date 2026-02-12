crypto_alice3(
	struct peer *peer,
	struct value *vp
	)
{
	DSA	*dsa;
	BN_CTX	*bctx;
	EVP_MD_CTX ctx;
	tstamp_t tstamp;
	u_int	len;


	if (peer->ident_pkey == NULL)
		return (XEVNT_ID);

	if ((dsa = peer->ident_pkey->pkey->pkey.dsa) == NULL) {
		msyslog(LOG_NOTICE, "crypto_alice3: defective key");
		return (XEVNT_PUB);
	}


	if (peer->iffval != NULL)
		BN_free(peer->iffval);
	peer->iffval = BN_new();
	len = BN_num_bytes(dsa->p);
	BN_rand(peer->iffval, len * 8, -1, 1);
	bctx = BN_CTX_new();
	BN_mod(peer->iffval, peer->iffval, dsa->p, bctx);
	BN_CTX_free(bctx);


	memset(vp, 0, sizeof(struct value));
	tstamp = crypto_time();
	vp->tstamp = htonl(tstamp);
	vp->fstamp = htonl(peer->ident_pkey->fstamp);
	vp->vallen = htonl(len);
	vp->ptr = emalloc(len);
	BN_bn2bin(peer->iffval, vp->ptr);
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
