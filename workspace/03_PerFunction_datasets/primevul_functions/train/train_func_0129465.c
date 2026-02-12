static bool is_chained_work(struct workqueue_struct *wq)
{
	struct worker *worker;

	worker = current_wq_worker();


	return worker && worker->current_pwq->wq == wq;
}
