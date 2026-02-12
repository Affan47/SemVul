int __init early_acpi_boot_init(void)
{


	if (acpi_disabled)
		return 1;


	early_acpi_process_madt();


	acpi_reduced_hw_init();

	return 0;
}
