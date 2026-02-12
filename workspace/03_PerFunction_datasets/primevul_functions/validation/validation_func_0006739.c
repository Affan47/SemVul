static __always_inline bool slab_free_hook(struct kmem_cache *s, void *x)
{
	kmemleak_free_recursive(x, s->flags);


#ifdef CONFIG_LOCKDEP
	{
		unsigned long flags;

		local_irq_save(flags);
		debug_check_no_locks_freed(x, s->object_size);
		local_irq_restore(flags);
	}
#endif
	if (!(s->flags & SLAB_DEBUG_OBJECTS))
		debug_check_no_obj_freed(x, s->object_size);


	return kasan_slab_free(s, x, _RET_IP_);
}
