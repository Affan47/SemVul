static inline void *kmalloc_large_node_hook(void *ptr, size_t size, gfp_t flags)
{
	ptr = kasan_kmalloc_large(ptr, size, flags);

	kmemleak_alloc(ptr, size, 1, flags);
	return ptr;
}
