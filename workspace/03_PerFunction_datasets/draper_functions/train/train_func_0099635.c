opensslgost_createctx(dst_key_t *key, dst_context_t *dctx) {
	EVP_MD_CTX *evp_md_ctx;
	const EVP_MD *md = EVP_gost();

	UNUSED(key);

	if (md == NULL)
		return (DST_R_OPENSSLFAILURE);

	evp_md_ctx = EVP_MD_CTX_create();
	if (evp_md_ctx == NULL)
		return (ISC_R_NOMEMORY);

	if (!EVP_DigestInit_ex(evp_md_ctx, md, NULL)) {
		EVP_MD_CTX_destroy(evp_md_ctx);
		return (ISC_R_FAILURE);
	}
	dctx->ctxdata.evp_md_ctx = evp_md_ctx;

	return (ISC_R_SUCCESS);
}
