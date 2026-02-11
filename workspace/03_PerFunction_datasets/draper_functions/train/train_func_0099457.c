mono_threads_add_async_job (MonoThreadInfo *info, MonoAsyncJob job)
{
	MonoAsyncJob old_job;
	do {
		old_job = (MonoAsyncJob) info->service_requests;
		if (old_job & job)
			return FALSE;
	} while (InterlockedCompareExchange (&info->service_requests, old_job | job, old_job) != old_job);
	return TRUE;
}
