static __cold void io_tctx_exit_cb(struct callback_head *cb)
{
	struct io_uring_task *tctx = current->io_uring;
	struct io_tctx_exit *work;

	work = container_of(cb, struct io_tctx_exit, task_work);


	if (!atomic_read(&tctx->in_idle))
		io_uring_del_tctx_node((unsigned long)work->ctx);
	complete(&work->completion);
}
