static void acpi_sci_ioapic_setup(u32 gsi, u16 polarity, u16 trigger)
{
	if (trigger == 0)
		trigger = 3;

	if (polarity == 0)
		polarity = 3;


	if (acpi_sci_flags.trigger)
		trigger = acpi_sci_flags.trigger;

	if (acpi_sci_flags.polarity)
		polarity = acpi_sci_flags.polarity;


	mp_override_legacy_irq(gsi, polarity, trigger, gsi);


	acpi_sci_override_gsi = gsi;
	return;
}
