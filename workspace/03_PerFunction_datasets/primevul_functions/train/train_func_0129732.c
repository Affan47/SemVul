int __init efi_setup_page_tables(unsigned long pa_memmap, unsigned num_pages)
{
	unsigned long pfn, text, pf;
	struct page *page;
	unsigned npages;
	pgd_t *pgd = efi_mm.pgd;

	if (efi_enabled(EFI_OLD_MEMMAP))
		return 0;


	pfn = pa_memmap >> PAGE_SHIFT;
	pf = _PAGE_NX | _PAGE_RW | _PAGE_ENC;
	if (kernel_map_pages_in_pgd(pgd, pfn, pa_memmap, num_pages, pf)) {
		pr_err("Error ident-mapping new memmap (0x%lx)!\n", pa_memmap);
		return 1;
	}


	pf = _PAGE_RW;
	if (sev_active())
		pf |= _PAGE_ENC;

	if (kernel_map_pages_in_pgd(pgd, 0x0, 0x0, 1, pf)) {
		pr_err("Failed to create 1:1 mapping for the first page!\n");
		return 1;
	}


	if (!IS_ENABLED(CONFIG_EFI_MIXED) || efi_is_native())
		return 0;

	page = alloc_page(GFP_KERNEL|__GFP_DMA32);
	if (!page)
		panic("Unable to allocate EFI runtime stack < 4GB\n");

	efi_scratch.phys_stack = virt_to_phys(page_address(page));
	efi_scratch.phys_stack += PAGE_SIZE;

	npages = (_etext - _text) >> PAGE_SHIFT;
	text = __pa(_text);
	pfn = text >> PAGE_SHIFT;

	pf = _PAGE_RW | _PAGE_ENC;
	if (kernel_map_pages_in_pgd(pgd, pfn, text, npages, pf)) {
		pr_err("Failed to map kernel text 1:1\n");
		return 1;
	}

	return 0;
}
