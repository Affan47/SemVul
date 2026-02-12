static int io_req_task_work_add(struct io_kiocb *req)
{
	struct task_struct *tsk = req->task;
	struct io_uring_task *tctx = tsk->io_uring;
	enum task_work_notify_mode notify;
	struct io_wq_work_node *node, *prev;
	unsigned long flags;
	int ret = 0;

	if (unlikely(tsk->flags & PF_EXITING))
		return -ESRCH;

	WARN_ON_ONCE(!tctx);

	spin_lock_irqsave(&tctx->task_lock, flags);
	wq_list_add_tail(&req->io_task_work.node, &tctx->task_list);
	spin_unlock_irqrestore(&tctx->task_lock, flags);


	if (test_bit(0, &tctx->task_state) ||
	    test_and_set_bit(0, &tctx->task_state))
		return 0;


	notify = (req->ctx->flags & IORING_SETUP_SQPOLL) ? TWA_NONE : TWA_SIGNAL;

	if (!task_work_add(tsk, &tctx->task_work, notify)) {
		wake_up_process(tsk);
		return 0;
	}


	spin_lock_irqsave(&tctx->task_lock, flags);
	wq_list_for_each(node, prev, &tctx->task_list) {
		if (&req->io_task_work.node == node) {
			wq_list_del(&tctx->task_list, node, prev);
			ret = 1;
			break;
		}
	}
	spin_unlock_irqrestore(&tctx->task_lock, flags);
	clear_bit(0, &tctx->task_state);
	return ret;
}
