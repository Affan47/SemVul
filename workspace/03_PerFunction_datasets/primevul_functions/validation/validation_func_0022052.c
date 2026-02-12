int __init acpi_boot_init(void)
{


	if (acpi_disabled && !acpi_ht)
		return 1;

	acpi_table_parse(ACPI_BOOT, acpi_parse_sbf);


	acpi_table_parse(ACPI_FADT, acpi_parse_fadt);


	acpi_process_madt();

	acpi_table_parse(ACPI_HPET, acpi_parse_hpet);

	return 0;
}
