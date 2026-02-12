static void pwq_dec_nr_in_flight(struct pool_workqueue *pwq, int color)
{

	if (color == WORK_NO_COLOR)
		goto out_put;

	pwq->nr_in_flight[color]--;

	pwq->nr_active--;
	if (!list_empty(&pwq->delayed_works)) {

		if (pwq->nr_active < pwq->max_active)
			pwq_activate_first_delayed(pwq);
	}


	if (likely(pwq->flush_color != color))
		goto out_put;


	if (pwq->nr_in_flight[color])
		goto out_put;


	pwq->flush_color = -1;


	if (atomic_dec_and_test(&pwq->wq->nr_pwqs_to_flush))
		complete(&pwq->wq->first_flusher->done);
out_put:
	put_pwq(pwq);
}
