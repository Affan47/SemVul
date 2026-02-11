acpi_pci_irq_disable(struct pci_dev *dev)
{
	struct acpi_prt_entry *entry;
	int gsi;
	u8 pin;

	pin = dev->pin;
	if (!pin || !dev->irq_managed || dev->irq <= 0)
		return;


	if (dev->dev.power.is_prepared)
		return;
#ifdef	CONFIG_PM
	if (dev->dev.power.runtime_status == RPM_SUSPENDING)
		return;
#endif

	entry = acpi_pci_irq_lookup(dev, pin);
	if (!entry)
		return;

	if (entry->link)
		gsi = acpi_pci_link_free_irq(entry->link);
	else
		gsi = entry->index;

	kfree(entry);


	dev_dbg(&dev->dev, "PCI INT %c disabled\n", pin_name(pin));
	if (gsi >= 0) {
		acpi_unregister_gsi(gsi);
		dev->irq_managed = 0;
	}
}
