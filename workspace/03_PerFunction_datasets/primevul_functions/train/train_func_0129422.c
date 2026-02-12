static int try_to_grab_pending(struct work_struct *work, bool is_dwork,
			       unsigned long *flags)
{
	struct worker_pool *pool;
	struct pool_workqueue *pwq;

	local_irq_save(*flags);


	if (is_dwork) {
		struct delayed_work *dwork = to_delayed_work(work);


		if (likely(del_timer(&dwork->timer)))
			return 1;
	}


	if (!test_and_set_bit(WORK_STRUCT_PENDING_BIT, work_data_bits(work)))
		return 0;


	pool = get_work_pool(work);
	if (!pool)
		goto fail;

	spin_lock(&pool->lock);


	pwq = get_work_pwq(work);
	if (pwq && pwq->pool == pool) {
		debug_work_deactivate(work);


		if (*work_data_bits(work) & WORK_STRUCT_DELAYED)
			pwq_activate_delayed_work(work);

		list_del_init(&work->entry);
		pwq_dec_nr_in_flight(pwq, get_work_color(work));


		set_work_pool_and_keep_pending(work, pool->id);

		spin_unlock(&pool->lock);
		return 1;
	}
	spin_unlock(&pool->lock);
fail:
	local_irq_restore(*flags);
	if (work_is_canceling(work))
		return -ENOENT;
	cpu_relax();
	return -EAGAIN;
}
