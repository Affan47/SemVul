static int ep_poll(struct eventpoll *ep, struct epoll_event __user *events,
		   int maxevents, long timeout)
{
	int res = 0, eavail, timed_out = 0;
	u64 slack = 0;
	wait_queue_entry_t wait;
	ktime_t expires, *to = NULL;

	lockdep_assert_irqs_enabled();

	if (timeout > 0) {
		struct timespec64 end_time = ep_set_mstimeout(timeout);

		slack = select_estimate_accuracy(&end_time);
		to = &expires;
		*to = timespec64_to_ktime(end_time);
	} else if (timeout == 0) {


		timed_out = 1;

		write_lock_irq(&ep->lock);
		eavail = ep_events_available(ep);
		write_unlock_irq(&ep->lock);

		goto send_events;
	}

fetch_events:

	if (!ep_events_available(ep))
		ep_busy_loop(ep, timed_out);

	eavail = ep_events_available(ep);
	if (eavail)
		goto send_events;


	ep_reset_busy_poll_napi_id(ep);

	do {


		init_wait(&wait);

		write_lock_irq(&ep->lock);


		__set_current_state(TASK_INTERRUPTIBLE);


		eavail = ep_events_available(ep);
		if (!eavail) {
			if (signal_pending(current))
				res = -EINTR;
			else
				__add_wait_queue_exclusive(&ep->wq, &wait);
		}
		write_unlock_irq(&ep->lock);

		if (eavail || res)
			break;

		if (!schedule_hrtimeout_range(to, slack, HRTIMER_MODE_ABS)) {
			timed_out = 1;
			break;
		}


		eavail = 1;

	} while (0);

	__set_current_state(TASK_RUNNING);

	if (!list_empty_careful(&wait.entry)) {
		write_lock_irq(&ep->lock);
		__remove_wait_queue(&ep->wq, &wait);
		write_unlock_irq(&ep->lock);
	}

send_events:
	if (fatal_signal_pending(current)) {


		res = -EINTR;
	}


	if (!res && eavail &&
	    !(res = ep_send_events(ep, events, maxevents)) && !timed_out)
		goto fetch_events;

	return res;
}
