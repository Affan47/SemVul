DetermineSleepTime(struct timeval *timeout)
{
	TimestampTz next_wakeup = 0;


	if (Shutdown > NoShutdown ||
		(!StartWorkerNeeded && !HaveCrashedWorker))
	{
		if (AbortStartTime != 0)
		{

			timeout->tv_sec = SIGKILL_CHILDREN_AFTER_SECS -
				(time(NULL) - AbortStartTime);
			timeout->tv_sec = Max(timeout->tv_sec, 0);
			timeout->tv_usec = 0;
		}
		else
		{
			timeout->tv_sec = 60;
			timeout->tv_usec = 0;
		}
		return;
	}

	if (StartWorkerNeeded)
	{
		timeout->tv_sec = 0;
		timeout->tv_usec = 0;
		return;
	}

	if (HaveCrashedWorker)
	{
		slist_mutable_iter siter;


		slist_foreach_modify(siter, &BackgroundWorkerList)
		{
			RegisteredBgWorker *rw;
			TimestampTz this_wakeup;

			rw = slist_container(RegisteredBgWorker, rw_lnode, siter.cur);

			if (rw->rw_crashed_at == 0)
				continue;

			if (rw->rw_worker.bgw_restart_time == BGW_NEVER_RESTART
				|| rw->rw_terminate)
			{
				ForgetBackgroundWorker(&siter);
				continue;
			}

			this_wakeup = TimestampTzPlusMilliseconds(rw->rw_crashed_at,
													  1000L * rw->rw_worker.bgw_restart_time);
			if (next_wakeup == 0 || this_wakeup < next_wakeup)
				next_wakeup = this_wakeup;
		}
	}

	if (next_wakeup != 0)
	{
		long		secs;
		int			microsecs;

		TimestampDifference(GetCurrentTimestamp(), next_wakeup,
							&secs, &microsecs);
		timeout->tv_sec = secs;
		timeout->tv_usec = microsecs;


		if (timeout->tv_sec > 60)
		{
			timeout->tv_sec = 60;
			timeout->tv_usec = 0;
		}
	}
	else
	{
		timeout->tv_sec = 60;
		timeout->tv_usec = 0;
	}
}
