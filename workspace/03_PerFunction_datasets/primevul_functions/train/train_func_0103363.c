static int __init early_acpi_parse_madt_lapic_addr_ovr(void)
{
	int count;

	if (!boot_cpu_has(X86_FEATURE_APIC))
		return -ENODEV;


	count = acpi_table_parse_madt(ACPI_MADT_TYPE_LOCAL_APIC_OVERRIDE,
				      acpi_parse_lapic_addr_ovr, 0);
	if (count < 0) {
		printk(KERN_ERR PREFIX
		       "Error parsing LAPIC address override entry\n");
		return count;
	}

	register_lapic_address(acpi_lapic_addr);

	return count;
}
