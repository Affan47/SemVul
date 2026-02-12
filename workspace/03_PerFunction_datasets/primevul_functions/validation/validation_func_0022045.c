static int __init acpi_parse_madt_lapic_entries(void)
{
	int count;

	if (!cpu_has_apic)
		return -ENODEV;


	count =
	    acpi_table_parse_madt(ACPI_MADT_LAPIC_ADDR_OVR,
				  acpi_parse_lapic_addr_ovr, 0);
	if (count < 0) {
		printk(KERN_ERR PREFIX
		       "Error parsing LAPIC address override entry\n");
		return count;
	}

	mp_register_lapic_address(acpi_lapic_addr);

	count = acpi_table_parse_madt(ACPI_MADT_LAPIC, acpi_parse_lapic,
				      MAX_APICS);
	if (!count) {
		printk(KERN_ERR PREFIX "No LAPIC entries present\n");

		return -ENODEV;
	} else if (count < 0) {
		printk(KERN_ERR PREFIX "Error parsing LAPIC entry\n");

		return count;
	}

	count =
	    acpi_table_parse_madt(ACPI_MADT_LAPIC_NMI, acpi_parse_lapic_nmi, 0);
	if (count < 0) {
		printk(KERN_ERR PREFIX "Error parsing LAPIC NMI entry\n");

		return count;
	}
	return 0;
}
