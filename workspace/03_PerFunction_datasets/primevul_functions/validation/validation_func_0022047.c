static int __init acpi_parse_fadt(unsigned long phys, unsigned long size)
{
	struct fadt_descriptor *fadt = NULL;

	fadt = (struct fadt_descriptor *)__acpi_map_table(phys, size);
	if (!fadt) {
		printk(KERN_WARNING PREFIX "Unable to map FADT\n");
		return 0;
	}

	acpi_fadt.sci_int = fadt->sci_int;


	acpi_fadt.revision = fadt->revision;
	acpi_fadt.force_apic_physical_destination_mode =
	    fadt->force_apic_physical_destination_mode;

#ifdef CONFIG_X86_PM_TIMER

	if (fadt->revision >= FADT2_REVISION_ID) {

		if (fadt->xpm_tmr_blk.address_space_id !=
		    ACPI_ADR_SPACE_SYSTEM_IO)
			return 0;

		pmtmr_ioport = fadt->xpm_tmr_blk.address;


		if (!pmtmr_ioport)
			pmtmr_ioport = fadt->V1_pm_tmr_blk;
	} else {

		pmtmr_ioport = fadt->V1_pm_tmr_blk;
	}
	if (pmtmr_ioport)
		printk(KERN_INFO PREFIX "PM-Timer IO Port: %#x\n",
		       pmtmr_ioport);
#endif
	return 0;
}
