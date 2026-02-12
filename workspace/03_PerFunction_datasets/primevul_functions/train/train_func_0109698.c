void __weak arch_uprobe_copy_ixol(struct page *page, unsigned long vaddr,
				  void *src, unsigned long len)
{

	copy_to_page(page, vaddr, src, len);


	flush_dcache_page(page);
}
