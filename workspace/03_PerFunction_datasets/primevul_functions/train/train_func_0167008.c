static inline struct kiocb *aio_get_req(struct kioctx *ctx)
{
	struct kiocb *req;


	req = __aio_get_req(ctx);
	if (unlikely(NULL == req)) {
		aio_fput_routine(NULL);
		req = __aio_get_req(ctx);
	}
	return req;
}
