crypt_convert_block(struct crypt_config *cc,
			       struct convert_context *ctx,
			       struct ablkcipher_request *req)
{
	struct bio_vec bv_in = bio_iter_iovec(ctx->bio_in, ctx->iter_in);
	struct bio_vec bv_out = bio_iter_iovec(ctx->bio_out, ctx->iter_out);
	struct dm_crypt_request *dmreq;
	u8 *iv;
	int r;

	dmreq = dmreq_of_req(cc, req);
	iv = iv_of_dmreq(cc, dmreq);

	dmreq->iv_sector = ctx->cc_sector;
	dmreq->ctx = ctx;
	sg_init_table(&dmreq->sg_in, 1);
	sg_set_page(&dmreq->sg_in, bv_in.bv_page, 1 << SECTOR_SHIFT,
		    bv_in.bv_offset);

	sg_init_table(&dmreq->sg_out, 1);
	sg_set_page(&dmreq->sg_out, bv_out.bv_page, 1 << SECTOR_SHIFT,
		    bv_out.bv_offset);

	bio_advance_iter(ctx->bio_in, &ctx->iter_in, 1 << SECTOR_SHIFT);
	bio_advance_iter(ctx->bio_out, &ctx->iter_out, 1 << SECTOR_SHIFT);

	if (cc->iv_gen_ops) {
		r = cc->iv_gen_ops->generator(cc, iv, dmreq);
		if (r < 0)
			return r;
	}

	ablkcipher_request_set_crypt(req, &dmreq->sg_in, &dmreq->sg_out,
				     1 << SECTOR_SHIFT, iv);

	if (bio_data_dir(ctx->bio_in) == WRITE)
		r = crypto_ablkcipher_encrypt(req);
	else
		r = crypto_ablkcipher_decrypt(req);

	if (!r && cc->iv_gen_ops && cc->iv_gen_ops->post)
		r = cc->iv_gen_ops->post(cc, iv, dmreq);

	return r;
}
