static void apply_wqattrs_lock(void)
{

	get_online_cpus();
	mutex_lock(&wq_pool_mutex);
}
