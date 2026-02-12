static inline struct page *shmem_dir_alloc(gfp_t gfp_mask)
{


	return alloc_pages((gfp_mask & ~GFP_MOVABLE_MASK) | __GFP_ZERO,
				PAGE_CACHE_SHIFT-PAGE_SHIFT);
}
