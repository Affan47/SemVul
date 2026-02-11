tcsd_threads_init(void)
{

	tm = calloc(1, sizeof(struct tcsd_thread_mgr));
	if (tm == NULL) {
		LogError("malloc of %zd bytes failed.", sizeof(struct tcsd_thread_mgr));
		return TCSERR(TSS_E_OUTOFMEMORY);
	}

	MUTEX_INIT(tm->lock);


	tm->max_threads = tcsd_options.num_threads;


	tm->thread_data = calloc(tcsd_options.num_threads, sizeof(struct tcsd_thread_data));
	if (tm->thread_data == NULL) {
		LogError("malloc of %zu bytes failed.",
			 tcsd_options.num_threads * sizeof(struct tcsd_thread_data));
		free(tm);
		return TCSERR(TSS_E_OUTOFMEMORY);
	}

	return TSS_SUCCESS;
}
