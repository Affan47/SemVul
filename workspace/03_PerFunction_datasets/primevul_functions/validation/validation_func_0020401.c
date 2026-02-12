static void io_uring_cancel_files(struct io_ring_ctx *ctx,
				  struct files_struct *files)
{
	if (list_empty_careful(&ctx->inflight_list))
		return;


	io_wq_cancel_cb(ctx->io_wq, io_wq_files_match, files, true);

	while (!list_empty_careful(&ctx->inflight_list)) {
		struct io_kiocb *cancel_req = NULL, *req;
		DEFINE_WAIT(wait);

		spin_lock_irq(&ctx->inflight_lock);
		list_for_each_entry(req, &ctx->inflight_list, inflight_entry) {
			if (req->work.files != files)
				continue;

			if (!refcount_inc_not_zero(&req->refs))
				continue;
			cancel_req = req;
			break;
		}
		if (cancel_req)
			prepare_to_wait(&ctx->inflight_wait, &wait,
						TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(&ctx->inflight_lock);


		if (!cancel_req)
			break;

		if (cancel_req->flags & REQ_F_OVERFLOW) {
			spin_lock_irq(&ctx->completion_lock);
			list_del(&cancel_req->compl.list);
			cancel_req->flags &= ~REQ_F_OVERFLOW;

			io_cqring_mark_overflow(ctx);
			WRITE_ONCE(ctx->rings->cq_overflow,
				atomic_inc_return(&ctx->cached_cq_overflow));
			io_commit_cqring(ctx);
			spin_unlock_irq(&ctx->completion_lock);


			if (refcount_sub_and_test(2, &cancel_req->refs)) {
				io_free_req(cancel_req);
				finish_wait(&ctx->inflight_wait, &wait);
				continue;
			}
		} else {
			io_wq_cancel_work(ctx->io_wq, &cancel_req->work);
			io_put_req(cancel_req);
		}

		schedule();
		finish_wait(&ctx->inflight_wait, &wait);
	}
}
