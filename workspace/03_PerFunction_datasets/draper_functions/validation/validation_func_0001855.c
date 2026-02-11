emax_reached(cli_ctx *ctx) {
    fmap_t **ctx_fmap = ctx->fmap;
    if (!ctx_fmap)
	return;
    while(*ctx_fmap) {
	fmap_t *map = *ctx_fmap;
	map->dont_cache_flag = 1;
	ctx_fmap--;
    }
    cli_dbgmsg("emax_reached: marked parents as non cacheable\n");
}
