visor_periodic_work_start(struct periodic_work *pw)
{
	bool rc = false;

	write_lock(&pw->lock);
	if (pw->is_scheduled) {
		rc = false;
		goto unlock;
	}
	if (pw->want_to_stop) {
		rc = false;
		goto unlock;
	}
	INIT_DELAYED_WORK(&pw->work, &periodic_work_func);
	if (!queue_delayed_work(pw->workqueue, &pw->work,
				pw->jiffy_interval)) {
		rc = false;
		goto unlock;
	}
	pw->is_scheduled = true;
	rc = true;
unlock:
	write_unlock(&pw->lock);
	return rc;
}
