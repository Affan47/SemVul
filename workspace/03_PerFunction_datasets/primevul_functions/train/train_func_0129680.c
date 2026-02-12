void __init efi_map_region(efi_memory_desc_t *md)
{
	unsigned long size = md->num_pages << PAGE_SHIFT;
	u64 pa = md->phys_addr;

	if (efi_enabled(EFI_OLD_MEMMAP))
		return old_map_region(md);


	__map_region(md, md->phys_addr);


	if (!efi_is_native () && IS_ENABLED(CONFIG_EFI_MIXED)) {
		md->virt_addr = md->phys_addr;
		return;
	}

	efi_va -= size;


	if (!(pa & (PMD_SIZE - 1))) {
		efi_va &= PMD_MASK;
	} else {
		u64 pa_offset = pa & (PMD_SIZE - 1);
		u64 prev_va = efi_va;


		efi_va = (efi_va & PMD_MASK) + pa_offset;

		if (efi_va > prev_va)
			efi_va -= PMD_SIZE;
	}

	if (efi_va < EFI_VA_END) {
		pr_warn(FW_WARN "VA address range overflow!\n");
		return;
	}


	__map_region(md, efi_va);
	md->virt_addr = efi_va;
}
