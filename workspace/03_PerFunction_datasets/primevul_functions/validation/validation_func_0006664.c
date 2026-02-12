void __kmemcg_cache_deactivate(struct kmem_cache *s)
{


	slub_set_cpu_partial(s, 0);
	s->min_partial = 0;
}
