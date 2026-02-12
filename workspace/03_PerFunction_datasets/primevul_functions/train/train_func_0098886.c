static void xen_load_gdt(const struct desc_ptr *dtr)
{
	unsigned long va = dtr->address;
	unsigned int size = dtr->size + 1;
	unsigned long pfn, mfn;
	int level;
	pte_t *ptep;
	void *virt;


	BUG_ON(size > PAGE_SIZE);
	BUG_ON(va & ~PAGE_MASK);


	ptep = lookup_address(va, &level);
	BUG_ON(ptep == NULL);

	pfn = pte_pfn(*ptep);
	mfn = pfn_to_mfn(pfn);
	virt = __va(PFN_PHYS(pfn));

	make_lowmem_page_readonly((void *)va);
	make_lowmem_page_readonly(virt);

	if (HYPERVISOR_set_gdt(&mfn, size / sizeof(struct desc_struct)))
		BUG();
}
