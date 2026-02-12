void __init efi_runtime_update_mappings(void)
{
	efi_memory_desc_t *md;

	if (efi_enabled(EFI_OLD_MEMMAP)) {
		if (__supported_pte_mask & _PAGE_NX)
			runtime_code_page_mkexec();
		return;
	}


	if (efi_enabled(EFI_MEM_ATTR)) {
		efi_memattr_apply_permissions(NULL, efi_update_mem_attr);
		return;
	}


	if (!efi_enabled(EFI_NX_PE_DATA))
		return;

	for_each_efi_memory_desc(md) {
		unsigned long pf = 0;

		if (!(md->attribute & EFI_MEMORY_RUNTIME))
			continue;

		if (!(md->attribute & EFI_MEMORY_WB))
			pf |= _PAGE_PCD;

		if ((md->attribute & EFI_MEMORY_XP) ||
			(md->type == EFI_RUNTIME_SERVICES_DATA))
			pf |= _PAGE_NX;

		if (!(md->attribute & EFI_MEMORY_RO) &&
			(md->type != EFI_RUNTIME_SERVICES_CODE))
			pf |= _PAGE_RW;

		if (sev_active())
			pf |= _PAGE_ENC;

		efi_update_mappings(md, pf);
	}
}
