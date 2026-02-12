int __init acpi_boot_table_init(void)
{
	int error;

#ifdef __i386__
	dmi_check_system(acpi_dmi_table);
#endif


	if (acpi_disabled && !acpi_ht)
		return 1;


	error = acpi_table_init();
	if (error) {
		disable_acpi();
		return error;
	}

	acpi_table_parse(ACPI_BOOT, acpi_parse_sbf);


	error = acpi_blacklisted();
	if (error) {
		if (acpi_force) {
			printk(KERN_WARNING PREFIX "acpi=force override\n");
		} else {
			printk(KERN_WARNING PREFIX "Disabling ACPI support\n");
			disable_acpi();
			return error;
		}
	}

	return 0;
}
