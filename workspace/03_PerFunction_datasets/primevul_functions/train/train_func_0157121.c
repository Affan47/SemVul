static void mce_unmap_kpfn(unsigned long pfn)
{
	unsigned long decoy_addr;


#if PGDIR_SHIFT + 9 < 63
	decoy_addr = (pfn << PAGE_SHIFT) + (PAGE_OFFSET ^ BIT(63));
#else
#error "no unused virtual bit available"
#endif

	if (set_memory_np(decoy_addr, 1))
		pr_warn("Could not invalidate pfn=0x%lx from 1:1 map\n", pfn);
}
