get_memmap(mmap_desc_t *desc)
{
#define	ELILO_MEMMAP_SIZE_DEFAULT	(EFI_PAGE_SIZE*2)
#define	ELILO_MEMMAP_INC		(sizeof(EFI_MEMORY_DESCRIPTOR)<<1)

	EFI_STATUS status;

	desc->map_size = ELILO_MEMMAP_SIZE_DEFAULT;

	for(;;) {
		desc->md = (EFI_MEMORY_DESCRIPTOR *)alloc(desc->map_size, EfiLoaderData);

		if (desc->md == NULL) {
			ERR_PRT((L"failed to allocate memory map buffer"));
			return -1;
		}
		status = uefi_call_wrapper(BS->GetMemoryMap, 5, &desc->map_size, desc->md,
					&desc->cookie, &desc->desc_size, &desc->desc_version);
		if (status == EFI_SUCCESS) break;

		free(desc->md);

		if (status != EFI_BUFFER_TOO_SMALL) {
			ERR_PRT((L"failed to obtain memory map %r"));
			return -1;
		}
		desc->map_size += ELILO_MEMMAP_INC;
	}
	DBG_PRT((L"final get_memmap map_size=%d", desc->map_size));

	return 0;
}
