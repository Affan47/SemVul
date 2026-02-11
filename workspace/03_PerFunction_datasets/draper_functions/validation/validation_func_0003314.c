isl_seq_normalize(struct isl_ctx *ctx, isl_int *p, unsigned len)
{
	if (len == 0)
		return;
	isl_seq_gcd(p, len, &ctx->normalize_gcd);
	if (!isl_int_is_zero(ctx->normalize_gcd) &&
	    !isl_int_is_one(ctx->normalize_gcd))
		isl_seq_scale_down(p, p, ctx->normalize_gcd, len);
}
