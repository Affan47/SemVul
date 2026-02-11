jws_verify_hs256(jws_t* v, const char* key, size_t keylen)
{
  jws_status_t ret = JWS_ERROR;
  size_t hmacrawlen;
  unsigned char hmacraw[64];

#if 0
  HMAC_CTX ctx;
  HMAC_Init(&ctx, key, keylen, EVP_sha256());
  HMAC_Update(&ctx, (const unsigned char *)v.header64, v.header64len);
  HMAC_Update(&ctx, (const unsigned char *)".", 1);
  HMAC_Update(&ctx, (const unsigned char *)v.body64, v.body64len);

  unsigned int hmaclen;
  HMAC_Final(&ctx, hmacraw, &hmaclen);
  mu_check(64 == hmaclen);
  HMAC_CTX_cleanup(&ctx);

  mu_check(0 == CRYPTO_memcmp(hmacraw, v.sig, v.siglen));
#endif

  EVP_PKEY* pkey = NULL;
  EVP_MD_CTX* mdctx = NULL;

  pkey = EVP_PKEY_new_mac_key(EVP_PKEY_HMAC, NULL,
			      (const unsigned char*)key, keylen);
  if (pkey == NULL) goto err;
  mdctx = EVP_MD_CTX_create();
  if (mdctx == NULL) goto err;

  if (1 != EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, pkey)) goto err;
  if (1 != EVP_DigestSignUpdate(mdctx,
				(const unsigned char *)v->header64,
				v->header64len)) goto err;

  if (1 != EVP_DigestSignUpdate(mdctx,
				(const unsigned char *)".", 1)) goto err;
  if (1 != EVP_DigestSignUpdate(mdctx,
				(const unsigned char *)v->body64,
				v->body64len)) goto err;

  if (1 != EVP_DigestSignFinal(mdctx, NULL, &hmacrawlen)) goto err;

  if (32 != hmacrawlen) goto err;

  if (1 != EVP_DigestSignFinal(mdctx, hmacraw, &hmacrawlen)) goto err;

  if (0 == CRYPTO_memcmp(hmacraw, v->sig, v->siglen)) {
    ret = JWS_OK;
  } else {
    ret = JWS_FALSE;
  }

 err:

  if (mdctx) EVP_MD_CTX_destroy(mdctx);
  if (pkey) EVP_PKEY_free(pkey);
  return ret;
}
