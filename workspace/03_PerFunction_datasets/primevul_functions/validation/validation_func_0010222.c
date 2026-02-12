*/
void __io_uring_cancel(struct files_struct *files)
{
	struct io_uring_task *tctx = current->io_uring;
	DEFINE_WAIT(wait);
	s64 inflight;


	atomic_inc(&tctx->in_idle);
	do {

		inflight = tctx_inflight(tctx, !!files);
		if (!inflight)
			break;
		io_uring_try_cancel(files);
		prepare_to_wait(&tctx->wait, &wait, TASK_UNINTERRUPTIBLE);


		if (inflight == tctx_inflight(tctx, !!files))
			schedule();
		finish_wait(&tctx->wait, &wait);
	} while (1);
	atomic_dec(&tctx->in_idle);

	io_uring_clean_tctx(tctx);
	if (!files) {

		__io_uring_free(current);
	}
}
