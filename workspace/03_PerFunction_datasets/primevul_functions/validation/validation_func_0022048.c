acpi_scan_rsdp(unsigned long start, unsigned long length)
{
	unsigned long offset = 0;
	unsigned long sig_len = sizeof("RSD PTR ") - 1;


	for (offset = 0; offset < length; offset += 16) {
		if (strncmp((char *)(phys_to_virt(start) + offset), "RSD PTR ", sig_len))
			continue;
		return (start + offset);
	}

	return 0;
}
