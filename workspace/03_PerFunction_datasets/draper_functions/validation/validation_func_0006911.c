crypto_ccm_encrypt(struct aead_request *req)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_ccm_ctx *ctx = crypto_aead_ctx(aead);
	struct crypto_ccm_req_priv_ctx *pctx = crypto_ccm_reqctx(req);
	struct ablkcipher_request *abreq = &pctx->abreq;
	struct scatterlist *dst;
	unsigned int cryptlen = req->cryptlen;
	u8 *odata = pctx->odata;
	u8 *iv = req->iv;
	int err;

	err = crypto_ccm_init_crypt(req, odata);
	if (err)
		return err;

	err = crypto_ccm_auth(req, sg_next(pctx->src), cryptlen);
	if (err)
		return err;

	dst = pctx->src;
	if (req->src != req->dst)
		dst = pctx->dst;

	ablkcipher_request_set_tfm(abreq, ctx->ctr);
	ablkcipher_request_set_callback(abreq, pctx->flags,
					crypto_ccm_encrypt_done, req);
	ablkcipher_request_set_crypt(abreq, pctx->src, dst, cryptlen + 16, iv);
	err = crypto_ablkcipher_encrypt(abreq);
	if (err)
		return err;


	scatterwalk_map_and_copy(odata, sg_next(dst), cryptlen,
				 crypto_aead_authsize(aead), 1);
	return err;
}
