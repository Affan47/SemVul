void __kmemcg_cache_deactivate_after_rcu(struct kmem_cache *s)
{


	if (!__kmem_cache_shrink(s))
		sysfs_slab_remove(s);
}
