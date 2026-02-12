static inline void prb_flush_block(struct kbdq_core *pkc1,
		struct block_desc *pbd1, __u32 status)
{


#if ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE == 1
	u8 *start, *end;

	start = (u8 *)pbd1;


	start += PAGE_SIZE;

	end = (u8 *)PAGE_ALIGN((unsigned long)pkc1->pkblk_end);
	for (; start < end; start += PAGE_SIZE)
		flush_dcache_page(pgv_to_page(start));

	smp_wmb();
#endif


	BLOCK_STATUS(pbd1) = status;


#if ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE == 1
	start = (u8 *)pbd1;
	flush_dcache_page(pgv_to_page(start));

	smp_wmb();
#endif
}
