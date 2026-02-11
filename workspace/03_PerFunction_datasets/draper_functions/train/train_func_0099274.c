genwqe_reset_interrupt_capability(struct genwqe_dev *cd)
{
	struct pci_dev *pci_dev = cd->pci_dev;

	if (cd->flags & GENWQE_FLAG_MSI_ENABLED) {
		pci_disable_msi(pci_dev);
		cd->flags &= ~GENWQE_FLAG_MSI_ENABLED;
	}
}
