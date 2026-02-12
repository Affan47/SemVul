unsigned long __init acpi_find_rsdp(void)
{
	unsigned long rsdp_phys = 0;

	if (efi_enabled) {
		if (efi.acpi20 != EFI_INVALID_TABLE_ADDR)
			return efi.acpi20;
		else if (efi.acpi != EFI_INVALID_TABLE_ADDR)
			return efi.acpi;
	}


	rsdp_phys = acpi_scan_rsdp(0, 0x400);
	if (!rsdp_phys)
		rsdp_phys = acpi_scan_rsdp(0xE0000, 0x20000);

	return rsdp_phys;
}
