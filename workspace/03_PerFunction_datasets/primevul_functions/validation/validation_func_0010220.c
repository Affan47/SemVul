static void io_req_task_cancel(struct callback_head *cb)
{
	struct io_kiocb *req = container_of(cb, struct io_kiocb, task_work);
	struct io_ring_ctx *ctx = req->ctx;


	mutex_lock(&ctx->uring_lock);
	io_req_complete_failed(req, req->result);
	mutex_unlock(&ctx->uring_lock);
}
