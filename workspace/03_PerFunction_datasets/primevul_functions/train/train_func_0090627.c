static bool io_queue_worker_create(struct io_worker *worker,
				   struct io_wqe_acct *acct,
				   task_work_func_t func)
{
	struct io_wqe *wqe = worker->wqe;
	struct io_wq *wq = wqe->wq;


	if (test_bit(IO_WQ_BIT_EXIT, &wq->state))
		goto fail;
	if (!io_worker_get(worker))
		goto fail;


	if (test_bit(0, &worker->create_state) ||
	    test_and_set_bit_lock(0, &worker->create_state))
		goto fail_release;

	init_task_work(&worker->create_work, func);
	worker->create_index = acct->index;
	if (!task_work_add(wq->task, &worker->create_work, TWA_SIGNAL))
		return true;
	clear_bit_unlock(0, &worker->create_state);
fail_release:
	io_worker_release(worker);
fail:
	atomic_dec(&acct->nr_running);
	io_worker_ref_put(wq);
	return false;
}
