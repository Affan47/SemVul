static void quirk_iommu_rwbf(struct pci_dev *dev)
{


	pci_info(dev, "Forcing write-buffer flush capability\n");
	rwbf_quirk = 1;
}
