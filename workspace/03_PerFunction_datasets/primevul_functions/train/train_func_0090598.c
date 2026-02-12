static bool io_wqe_create_worker(struct io_wqe *wqe, struct io_wqe_acct *acct)
{
	bool do_create = false;


	if (unlikely(!acct->max_workers))
		pr_warn_once("io-wq is not configured for unbound workers");

	raw_spin_lock(&wqe->lock);
	if (acct->nr_workers < acct->max_workers) {
		acct->nr_workers++;
		do_create = true;
	}
	raw_spin_unlock(&wqe->lock);
	if (do_create) {
		atomic_inc(&acct->nr_running);
		atomic_inc(&wqe->wq->worker_refs);
		return create_io_worker(wqe->wq, wqe, acct->index);
	}

	return true;
}
