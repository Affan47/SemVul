glue_filesystem(EFI_GUID *proto, EFI_HANDLE dev, fops_fs_glue_t glue)
{
	fileops_t *fops;
	VOID *intf = NULL;
	EFI_STATUS status;

	status = uefi_call_wrapper(BS->HandleProtocol, 3, dev, proto, &intf);
	if (EFI_ERROR(status)) {
		ERR_PRT((L"unable to locate %g: should not happen", proto));
		return NULL;
	}
	fops = (fileops_t *)alloc(sizeof(*fops), EfiLoaderData);
	if (fops == NULL) {
		ERR_PRT((L"failed to allocate fileops"));
		return NULL;
	}
	Memset(fops, 0, sizeof(*fops));

	fops->dev = dev;


	glue(fops, intf);

	return fops;
}
