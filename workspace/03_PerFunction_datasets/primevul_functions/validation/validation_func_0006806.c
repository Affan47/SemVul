static inline void *freelist_ptr(const struct kmem_cache *s, void *ptr,
				 unsigned long ptr_addr)
{
#ifdef CONFIG_SLAB_FREELIST_HARDENED


	return (void *)((unsigned long)ptr ^ s->random ^
			(unsigned long)kasan_reset_tag((void *)ptr_addr));
#else
	return ptr;
#endif
}
