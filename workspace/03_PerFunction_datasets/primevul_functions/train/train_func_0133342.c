void http_check_request_for_cacheability(struct stream *s, struct channel *req)
{
	struct http_txn *txn = s->txn;
	struct htx *htx;
	struct http_hdr_ctx ctx = { .blk = NULL };
	int pragma_found, cc_found;

	if ((txn->flags & (TX_CACHEABLE|TX_CACHE_IGNORE)) == TX_CACHE_IGNORE)
		return;

	htx = htxbuf(&req->buf);
	pragma_found = cc_found = 0;


	if (http_find_header(htx, ist("pragma"), &ctx, 1)) {
		if (isteqi(ctx.value, ist("no-cache"))) {
			pragma_found = 1;
		}
	}

	ctx.blk = NULL;


	if (http_find_header(htx, ist("authorization"), &ctx, 1)) {
		txn->flags &= ~TX_CACHEABLE & ~TX_CACHE_COOK;
		txn->flags |= TX_CACHE_IGNORE;
	}


	ctx.blk = NULL;
	while (http_find_header(htx, ist("cache-control"), &ctx, 0)) {
		cc_found = 1;


		if (istmatchi(ctx.value, ist("max-age")) ||
		    istmatchi(ctx.value, ist("no-cache")) ||
		    istmatchi(ctx.value, ist("max-stale")) ||
		    istmatchi(ctx.value, ist("min-fresh"))) {
			txn->flags |= TX_CACHE_IGNORE;
			continue;
		}
		if (istmatchi(ctx.value, ist("no-store"))) {
			txn->flags &= ~TX_CACHEABLE & ~TX_CACHE_COOK;
			continue;
		}
	}


	if (!cc_found && pragma_found)
		txn->flags |= TX_CACHE_IGNORE;
}
