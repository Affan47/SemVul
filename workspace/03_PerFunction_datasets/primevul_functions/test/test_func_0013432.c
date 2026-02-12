static void esp_ssg_unref(struct xfrm_state *x, void *tmp)
{
	struct crypto_aead *aead = x->data;
	int extralen = 0;
	u8 *iv;
	struct aead_request *req;
	struct scatterlist *sg;

	if (x->props.flags & XFRM_STATE_ESN)
		extralen += sizeof(struct esp_output_extra);

	iv = esp_tmp_iv(aead, tmp, extralen);
	req = esp_tmp_req(aead, iv);


	if (req->src != req->dst)
		for (sg = sg_next(req->src); sg; sg = sg_next(sg))
			put_page(sg_page(sg));
}
