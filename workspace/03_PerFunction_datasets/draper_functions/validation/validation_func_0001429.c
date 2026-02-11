free_specific(void *arg) {
	dns_name_totextfilter_t *mem = arg;
	isc_mem_put(thread_key_mctx, mem, sizeof(*mem));

	(void)isc_thread_key_setspecific(totext_filter_proc_key, NULL);
}
