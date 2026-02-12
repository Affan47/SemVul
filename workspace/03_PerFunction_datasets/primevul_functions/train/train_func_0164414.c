static inline void shmem_swp_balance_unmap(void)
{


	(void) kmap_atomic(ZERO_PAGE(0), KM_USER1);
}
