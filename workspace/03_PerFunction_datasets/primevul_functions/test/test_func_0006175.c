rpmRC pgpVerifySignature(pgpDigParams key, pgpDigParams sig, DIGEST_CTX hashctx)
{
    DIGEST_CTX ctx = rpmDigestDup(hashctx);
    uint8_t *hash = NULL;
    size_t hashlen = 0;
    rpmRC res = RPMRC_FAIL;

    if (sig == NULL || ctx == NULL)
	goto exit;

    if (sig->hash != NULL)
	rpmDigestUpdate(ctx, sig->hash, sig->hashlen);

    if (sig->version == 4) {

	uint8_t trailer[6];
	uint32_t nb = sig->hashlen;
	nb = htonl(nb);
	trailer[0] = sig->version;
	trailer[1] = 0xff;
	memcpy(trailer+2, &nb, 4);
	rpmDigestUpdate(ctx, trailer, sizeof(trailer));
    }

    rpmDigestFinal(ctx, (void **)&hash, &hashlen, 0);


    if (hash == NULL || memcmp(hash, sig->signhash16, 2) != 0)
	goto exit;


    if (key && key->alg) {
	pgpDigAlg sa = sig->alg;
	pgpDigAlg ka = key->alg;
	if (sa && sa->verify) {
	    if (sa->verify(ka, sa, hash, hashlen, sig->hash_algo) == 0) {
		res = RPMRC_OK;
	    }
	}
    } else {
	res = RPMRC_NOKEY;
    }

exit:
    free(hash);
    return res;

}
