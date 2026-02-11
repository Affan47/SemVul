InputStream_read(CTX ctx, ksfp_t *sfp _RIX)
{
	kBytes *ba = sfp[1].ba;
	if(IS_NULL(ba)) {
		ba = new_Bytes(ctx, NULL, 4096);
		KNH_SETv(ctx, sfp[1].ba, ba);
		io2_readAll(ctx, (sfp[0].in)->io2, ba);
	}
	else {
		size_t len = Int_to2(size_t, sfp[2], ba->dim->capacity);
		if(!(len < ba->dim->capacity)) {
			THROW_OutOfRange(ctx, sfp, len, ba->dim->capacity);
		}
		len = io2_read(ctx, (sfp[0].in)->io2, ba->bu.buf, len);
		ba->bu.len = len;
	}
	RETURN_(ba);
}
