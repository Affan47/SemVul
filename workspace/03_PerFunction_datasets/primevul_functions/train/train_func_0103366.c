static int acpi_register_gsi_pic(struct device *dev, u32 gsi,
				 int trigger, int polarity)
{
#ifdef CONFIG_PCI


	if (trigger == ACPI_LEVEL_SENSITIVE)
		elcr_set_level_irq(gsi);
#endif

	return gsi;
}
