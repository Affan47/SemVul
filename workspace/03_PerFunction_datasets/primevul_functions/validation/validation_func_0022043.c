acpi_parse_lapic(acpi_table_entry_header * header, const unsigned long end)
{
	struct acpi_table_lapic *processor = NULL;

	processor = (struct acpi_table_lapic *)header;

	if (BAD_MADT_ENTRY(processor, end))
		return -EINVAL;

	acpi_table_print_madt_entry(header);


	if (processor->flags.enabled)
		x86_acpiid_to_apicid[processor->acpi_id] = processor->id;


	mp_register_lapic(processor->id,
			  processor->flags.enabled);

	return 0;
}
