generate_path(CHAR16* name, EFI_LOADED_IMAGE *li, EFI_DEVICE_PATH **path, CHAR16 **PathName)
{
	unsigned int pathlen;
	EFI_STATUS efi_status = EFI_SUCCESS;
	CHAR16 *devpathstr = DevicePathToStr(li->FilePath),
		*found = NULL;
	int i;

	for (i = 0; i < StrLen(devpathstr); i++) {
		if (devpathstr[i] == '/')
			devpathstr[i] = '\\';
		if (devpathstr[i] == '\\')
			found = &devpathstr[i];
	}
	if (!found) {
		pathlen = 0;
	} else {
		while (*(found - 1) == '\\')
			--found;
		*found = '\0';
		pathlen = StrLen(devpathstr);
	}

	if (name[0] != '\\')
		pathlen++;

	*PathName = AllocatePool((pathlen + 1 + StrLen(name))*sizeof(CHAR16));

	if (!*PathName) {
		Print(L"Failed to allocate path buffer\n");
		efi_status = EFI_OUT_OF_RESOURCES;
		goto error;
	}

	StrCpy(*PathName, devpathstr);

	if (name[0] != '\\')
		StrCat(*PathName, L"\\");
	StrCat(*PathName, name);

	*path = FileDevicePath(li->DeviceHandle, *PathName);

error:
	FreePool(devpathstr);

	return efi_status;
}
