static void quirk_iommu_rwbf(struct pci_dev *dev)
{


	pr_info("Forcing write-buffer flush capability\n");
	rwbf_quirk = 1;
}
