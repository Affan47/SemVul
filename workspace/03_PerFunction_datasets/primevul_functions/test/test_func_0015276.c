__must_hold(&ctx->completion_lock)
{
	u32 seq = ctx->cached_cq_tail - atomic_read(&ctx->cq_timeouts);
	struct io_kiocb *req, *tmp;

	spin_lock_irq(&ctx->timeout_lock);
	list_for_each_entry_safe(req, tmp, &ctx->timeout_list, timeout.list) {
		u32 events_needed, events_got;

		if (io_is_timeout_noseq(req))
			break;


		events_needed = req->timeout.target_seq - ctx->cq_last_tm_flush;
		events_got = seq - ctx->cq_last_tm_flush;
		if (events_got < events_needed)
			break;

		io_kill_timeout(req, 0);
	}
	ctx->cq_last_tm_flush = seq;
	spin_unlock_irq(&ctx->timeout_lock);
}
