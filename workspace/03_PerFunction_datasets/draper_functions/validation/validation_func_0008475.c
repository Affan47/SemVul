pci_msi_domain_write_msg(struct irq_data *irq_data, struct msi_msg *msg)
{
	struct msi_desc *desc = irq_data_get_msi_desc(irq_data);


	if (desc->irq == irq_data->irq)
		__pci_write_msi_msg(desc, msg);
}
