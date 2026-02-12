static int __init eventpoll_init(void)
{
	struct sysinfo si;

	si_meminfo(&si);


	max_user_watches = (((si.totalram - si.totalhigh) / 25) << PAGE_SHIFT) /
		EP_ITEM_COST;
	BUG_ON(max_user_watches < 0);


	ep_nested_calls_init(&poll_loop_ncalls);


	BUILD_BUG_ON(sizeof(void *) <= 8 && sizeof(struct epitem) > 128);


	epi_cache = kmem_cache_create("eventpoll_epi", sizeof(struct epitem),
			0, SLAB_HWCACHE_ALIGN|SLAB_PANIC|SLAB_ACCOUNT, NULL);


	pwq_cache = kmem_cache_create("eventpoll_pwq",
		sizeof(struct eppoll_entry), 0, SLAB_PANIC|SLAB_ACCOUNT, NULL);

	return 0;
}
