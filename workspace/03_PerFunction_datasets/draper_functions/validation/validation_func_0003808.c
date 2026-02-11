enroll_hash(int key)
{
	EFI_STATUS efi_status;
	CHAR16 *file_name = NULL, *title[6], buf0[256], buf1[256], buf2[256];
	UINT8 hash[SHA256_DIGEST_SIZE];
	int i;
	EFI_HANDLE h = NULL;

	simple_file_selector(&h, (CHAR16 *[]){
			L"Select Binary",
			L"",
			L"The Selected Binary will have its hash Enrolled",
			L"This means it will Subsequently Boot with no prompting",
			L"Remember to make sure it is a genuine binary before Enrolling its hash",
			NULL
		}, L"\\", NULL, &file_name);

	if (!file_name)

		return;

	efi_status = sha256_get_pecoff_digest(h, file_name, hash);
	if (efi_status != EFI_SUCCESS) {
		console_error(L"Hash failed (is efi binary valid?)",
			      efi_status);
		return;
	}

	StrCpy(buf0, L"Enroll hash into ");
	StrCat(buf0, keyinfo[key].text);
	title[0] = buf0;
	title[1] = L"";
	StrCpy(buf1, L"File: ");
	StrCat(buf1, file_name);
	title[2] = buf1;
	StrCpy(buf2, L"Hash: ");
	sha256_StrCat_hash(buf2, hash);
	title[3] = buf2;
	title[4] = NULL;
	i = console_yes_no(title);
	if (i == 0)
		return;

	efi_status = variable_enroll_hash(keyinfo[key].name,
					  *keyinfo[key].guid, hash);
	if (efi_status != EFI_SUCCESS && efi_status != EFI_ALREADY_STARTED) {
		console_error(L"Failed to add signature to db", efi_status);
		return;
	}
}
