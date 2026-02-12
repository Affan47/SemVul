static bool should_map_region(efi_memory_desc_t *md)
{


	if (md->attribute & EFI_MEMORY_RUNTIME)
		return true;


	if (IS_ENABLED(CONFIG_X86_32))
		return false;


	if (IS_ENABLED(CONFIG_EFI_MIXED) && !efi_is_native()) {
		if (md->type == EFI_CONVENTIONAL_MEMORY ||
		    md->type == EFI_LOADER_DATA ||
		    md->type == EFI_LOADER_CODE)
			return true;
	}


	if (md->type == EFI_BOOT_SERVICES_CODE ||
	    md->type == EFI_BOOT_SERVICES_DATA)
		return true;

	return false;
}
