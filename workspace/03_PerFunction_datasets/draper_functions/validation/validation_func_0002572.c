pcie_downstream_port(const struct pci_dev *dev)
{
	int type = pci_pcie_type(dev);

	return type == PCI_EXP_TYPE_ROOT_PORT ||
	       type == PCI_EXP_TYPE_DOWNSTREAM;
}
