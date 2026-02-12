static int io_req_task_work_add(struct io_kiocb *req, struct callback_head *cb)
{
	struct task_struct *tsk = req->task;
	struct io_ring_ctx *ctx = req->ctx;
	int ret, notify;


	notify = 0;
	if (!(ctx->flags & IORING_SETUP_SQPOLL))
		notify = TWA_SIGNAL;

	ret = task_work_add(tsk, cb, notify);
	if (!ret)
		wake_up_process(tsk);

	return ret;
}
