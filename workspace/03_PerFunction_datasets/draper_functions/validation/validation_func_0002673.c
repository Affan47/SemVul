init_cache_buckets(drm_intel_bufmgr_gem *bufmgr_gem)
{
	unsigned long size, cache_max_size = 64 * 1024 * 1024;


	add_bucket(bufmgr_gem, 4096);
	add_bucket(bufmgr_gem, 4096 * 2);
	add_bucket(bufmgr_gem, 4096 * 3);


	for (size = 4 * 4096; size <= cache_max_size; size *= 2) {
		add_bucket(bufmgr_gem, size);

		add_bucket(bufmgr_gem, size + size * 1 / 4);
		add_bucket(bufmgr_gem, size + size * 2 / 4);
		add_bucket(bufmgr_gem, size + size * 3 / 4);
	}
}
