unique_null_status(const char *s, void *ctx)
{
	const struct edit_unique_ctx *unique_ctx = ctx;

	if (!strcmp(s, *unique_ctx->s ? *unique_ctx->s : ""))
		return es_unchanged;
	if (!*s)
		return es_good;
	return !unique_ctx->validate ||
	    unique_ctx->validate(s, unique_ctx->ctx) ? es_good : es_bad;
}
