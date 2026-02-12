get_section_vma_by_name (char *name, size_t namesz,
			 char *buffer, size_t bufsz,
			 PE_COFF_LOADER_IMAGE_CONTEXT *context,
			 char **basep, size_t *sizep,
			 EFI_IMAGE_SECTION_HEADER **sectionp)
{
	UINTN i;
	char namebuf[9];

	if (!name || namesz == 0 || !buffer || bufsz < namesz || !context
	    || !basep || !sizep || !sectionp)
		return EFI_INVALID_PARAMETER;


	if (namesz > 8)
		return EFI_UNSUPPORTED;

	SetMem(namebuf, sizeof(namebuf), 0);
	CopyMem(namebuf, name, MIN(namesz, 8));


	for (i = 0; i < context->NumberOfSections; i++) {
		EFI_STATUS status;
		EFI_IMAGE_SECTION_HEADER *section = NULL;
		char *base = NULL;
		size_t size = 0;

		status = get_section_vma(i, buffer, bufsz, context, &base, &size, &section);
		if (!EFI_ERROR(status)) {
			if (CompareMem(section->Name, namebuf, 8) == 0) {
				*basep = base;
				*sizep = size;
				*sectionp = section;
				return EFI_SUCCESS;
			}
			continue;
		}

		switch(status) {
		case EFI_NOT_FOUND:
			break;
		}
	}

	return EFI_NOT_FOUND;
}
