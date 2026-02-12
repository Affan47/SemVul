static int __init efi_runtime_init(void)
{
	int rv;


	if (!efi_enabled(EFI_PARAVIRT)) {
		if (efi_enabled(EFI_64BIT))
			rv = efi_runtime_init64();
		else
			rv = efi_runtime_init32();

		if (rv)
			return rv;
	}

	set_bit(EFI_RUNTIME_SERVICES, &efi.flags);

	return 0;
}
