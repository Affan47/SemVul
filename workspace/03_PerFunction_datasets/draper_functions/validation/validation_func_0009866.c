ldap_pvt_thread_pool_getkey(
	void *xctx,
	void *key,
	void **data,
	ldap_pvt_thread_pool_keyfree_t **kfree )
{
	ldap_int_thread_userctx_t *ctx = xctx;
	int i;

	if ( !ctx || !key || !data ) return EINVAL;

	for ( i=0; i<MAXKEYS && ctx->ltu_key[i].ltk_key; i++ ) {
		if ( ctx->ltu_key[i].ltk_key == key ) {
			*data = ctx->ltu_key[i].ltk_data;
			if ( kfree ) *kfree = ctx->ltu_key[i].ltk_free;
			return 0;
		}
	}
	return ENOENT;
}
