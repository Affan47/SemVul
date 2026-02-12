static struct io_kiocb *io_alloc_req(struct io_ring_ctx *ctx)
{
	struct io_submit_state *state = &ctx->submit_state;

	BUILD_BUG_ON(ARRAY_SIZE(state->reqs) < IO_REQ_ALLOC_BATCH);

	if (!state->free_reqs) {
		gfp_t gfp = GFP_KERNEL | __GFP_NOWARN;
		int ret, i;

		if (io_flush_cached_reqs(ctx))
			goto got_req;

		ret = kmem_cache_alloc_bulk(req_cachep, gfp, IO_REQ_ALLOC_BATCH,
					    state->reqs);


		if (unlikely(ret <= 0)) {
			state->reqs[0] = kmem_cache_alloc(req_cachep, gfp);
			if (!state->reqs[0])
				return NULL;
			ret = 1;
		}


		for (i = 0; i < ret; i++) {
			struct io_kiocb *req = state->reqs[i];

			req->ctx = ctx;
			req->link = NULL;
			req->async_data = NULL;

			req->result = 0;
		}
		state->free_reqs = ret;
	}
got_req:
	state->free_reqs--;
	return state->reqs[state->free_reqs];
}
