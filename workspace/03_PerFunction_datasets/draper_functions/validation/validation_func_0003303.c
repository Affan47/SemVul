zs_shrinker_scan(struct shrinker *shrinker,
		struct shrink_control *sc)
{
	unsigned long pages_freed;
	struct zs_pool *pool = container_of(shrinker, struct zs_pool,
			shrinker);

	pages_freed = pool->stats.pages_compacted;


	pages_freed = zs_compact(pool) - pages_freed;

	return pages_freed ? pages_freed : SHRINK_STOP;
}
