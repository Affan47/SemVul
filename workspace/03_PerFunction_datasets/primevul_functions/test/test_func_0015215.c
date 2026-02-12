static __poll_t io_uring_poll(struct file *file, poll_table *wait)
{
	struct io_ring_ctx *ctx = file->private_data;
	__poll_t mask = 0;

	poll_wait(file, &ctx->cq_wait, wait);


	smp_rmb();
	if (!io_sqring_full(ctx))
		mask |= EPOLLOUT | EPOLLWRNORM;


	if (io_cqring_events(ctx) || test_bit(0, &ctx->check_cq_overflow))
		mask |= EPOLLIN | EPOLLRDNORM;

	return mask;
}
