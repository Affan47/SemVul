static int io_iopoll_check(struct io_ring_ctx *ctx, long min)
{
	unsigned int nr_events = 0;
	int ret = 0;


	mutex_lock(&ctx->uring_lock);


	if (test_bit(0, &ctx->check_cq_overflow))
		__io_cqring_overflow_flush(ctx, false);
	if (io_cqring_events(ctx))
		goto out;
	do {


		if (list_empty(&ctx->iopoll_list)) {
			u32 tail = ctx->cached_cq_tail;

			mutex_unlock(&ctx->uring_lock);
			io_run_task_work();
			mutex_lock(&ctx->uring_lock);


			if (tail != ctx->cached_cq_tail ||
			    list_empty(&ctx->iopoll_list))
				break;
		}
		ret = io_do_iopoll(ctx, &nr_events, min);
	} while (!ret && nr_events < min && !need_resched());
out:
	mutex_unlock(&ctx->uring_lock);
	return ret;
}
