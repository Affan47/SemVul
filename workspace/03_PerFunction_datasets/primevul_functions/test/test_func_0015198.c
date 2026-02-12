static void __io_req_complete_post(struct io_kiocb *req, s32 res,
				   u32 cflags)
{
	struct io_ring_ctx *ctx = req->ctx;

	if (!(req->flags & REQ_F_CQE_SKIP))
		__io_fill_cqe_req(req, res, cflags);


	if (req_ref_put_and_test(req)) {
		if (req->flags & (REQ_F_LINK | REQ_F_HARDLINK)) {
			if (req->flags & IO_DISARM_MASK)
				io_disarm_next(req);
			if (req->link) {
				io_req_task_queue(req->link);
				req->link = NULL;
			}
		}
		io_req_put_rsrc(req, ctx);


		io_put_kbuf_comp(req);
		io_dismantle_req(req);
		io_put_task(req->task, 1);
		wq_list_add_head(&req->comp_list, &ctx->locked_free_list);
		ctx->locked_free_nr++;
	}
}
