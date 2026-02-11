init_ts_event_alloc(void)
{
    free_ts_ev = ts_event_pool(ERTS_TS_EV_ALLOC_DEFAULT_POOL_SIZE,
			       NULL);
    if (!free_ts_ev)
	return ENOMEM;
    return ethr_spinlock_init(&ts_ev_alloc_lock);
}
